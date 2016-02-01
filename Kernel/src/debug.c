#include <debug.h>
#include <stdarg.h>
#include <liba.h>
#include <strings.h>

// TODO: 

#define _PORT_COM1 0x3F8   /* COM1 */

#define BASE_BINARY 2 // TODO: Cambiar de lugar! numbers.h en shared lib?
#define BASE_DECIMAL 10
#define BASE_HEXADECIMAL 16

#define CONVERT_BUFFER_SIZE 128
static char convert_buffer[CONVERT_BUFFER_SIZE] = {0}; // TODO: Cambiar de lugar!!

static void debug_write(char character);
static int debug_print(char * string);
static void debug_digit(int number, unsigned int base);
static int is_transmit_empty();
static void write_serial(char a);

void debug_init() {
   _port_write_byte(_PORT_COM1 + 1, 0x00);    // Disable all interrupts
   _port_write_byte(_PORT_COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   _port_write_byte(_PORT_COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   _port_write_byte(_PORT_COM1 + 1, 0x00);    //                  (hi byte)
   _port_write_byte(_PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
   _port_write_byte(_PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   _port_write_byte(_PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int debug(char * fmt, ...) { // TODO: How to set styles
    char symbol;
    int i = 0;
    va_list arg;

    va_start(arg, fmt);
    while(fmt[i] != 0) {
		if(fmt[i] == '%') {
			symbol = fmt[++i];
		    switch(symbol) {
		    	case 's':
					debug_print(va_arg(arg, char *));
					break;
				case 'c':
					debug_write(va_arg(arg, int));
					break;
				case 'd':
					debug_digit(va_arg(arg, int), BASE_DECIMAL);
					break;
				case 'h':
					debug_digit(va_arg(arg, int), BASE_HEXADECIMAL);
					break;
				case 'b':
					debug_digit(va_arg(arg, int), BASE_BINARY);
					break;
				case '%':
					debug_write(symbol);
					break;
			}
		} else {
			debug_write(fmt[i]);
		}

		i++;
	}
	va_end(arg);

	return i - 1;
}

static void debug_write(char character) {
	write_serial(character);
}

static int debug_print(char * string) {
	int i = 0;

	while(string[i]) {
		debug_write(string[i++]);
	}

	return i;
}

static void debug_digit(int number, unsigned int base) {
	intstr(number, base, convert_buffer);

	// TODO: Choose
	// if(number < 0) {
	// 	terminal_write(terminal, '-');
	// }
	// if(base == BASE_HEXADECIMAL) {
	// 	terminal_print(terminal, "0x");
	// }
	// terminal_print(terminal, convert_buffer + 1);

	debug_print(convert_buffer);

	switch(base) {
		case BASE_BINARY:
			debug_write('b');
			break;
		case BASE_HEXADECIMAL:
			debug_write('h');
			break;
		default:
			break;
	}
}

static int is_transmit_empty() {
   return _port_read_byte(_PORT_COM1 + 5) & 0x20;
}
 
static void write_serial(char a) {
   while(is_transmit_empty() == 0);
 
   _port_write_byte(_PORT_COM1,a);
}