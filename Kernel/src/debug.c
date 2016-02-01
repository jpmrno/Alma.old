#include <debug.h>
#include <stdarg.h>
#include <serial.h>
#include <strings.h>

// TODO: 

#define BASE_BINARY 2 // TODO: Cambiar de lugar! numbers.h en shared lib?
#define BASE_DECIMAL 10
#define BASE_HEXADECIMAL 16

#define CONVERT_BUFFER_SIZE 128
static char convert_buffer[CONVERT_BUFFER_SIZE] = {0}; // TODO: Cambiar de lugar!!

static void debug_write(char character);
static int debug_print(char * string);
static void debug_digit(int number, unsigned int base);

void debug_init() {
	if(!serial_isInit()) {
		serial_init();
	}
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
	serial_write(character);
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
