#include <stdio.h>
#include <define.h>
#include <limits.h>
#include <strings.h>
#include <numbers.h>

#define CONVERT_BUFFER_SIZE 128 // TODO: Cambiar cuando pueda alocar memoria?
static char convert_buffer[CONVERT_BUFFER_SIZE] = {0}; // TODO: Cambiar cuando pueda alocar memoria?

extern unsigned int sysread(char * buffer, unsigned int length);
extern unsigned int syswrite(char * string, unsigned int length);

int scanc() {
	char c;
	int ret = sysread(&c, 1);

	if(ret != EOF) {
		ret = c;
	}

	return ret;
}

int scanf(char * buffer, int maxSize) {
	int length = scanw(buffer, maxSize);

	buffer[length] = 0;
	
	return length;
}

int scanw(char * buffer, int maxSize) {
	int c;
	int i = 0; // points to the next position where to insert

	do {
		c = scanc();

		if(c != EOF) {
			buffer[i++] = c;
		}
	} while(c != ' ' && c != '\n' && c != 0 && c != EOF && i < maxSize);

	return i - 1;
}

int printc(char character) {
	return syswrite(&character, 1);
}

int prints(char * string) {
	return syswrite(string, UINT_MAX);
}

int printn(int number, unsigned int base) {
	int printed = prints(strnum(number, base, convert_buffer));

	switch(base) {
		case _NUMBERS_BASE_BIN:
			printed += printc('b');
			break;
		case _NUMBERS_BASE_HEX:
			printed += printc('h');
			break;
		default:
			break;
	}

	return printed;
}

int printf(char * fmt, ...) {
    int printed = 0;
    va_list arg;

    va_start(arg, fmt);
    printed = vprintf(fmt, arg);
	va_end(arg);

	return printed;
}

int vprintf(char * fmt, va_list arg) { // TODO: How to set styles
    char symbol;
    int i = 0;
    int printed = 0;

    while(fmt[i] != 0) {
		if(fmt[i] == '%') {
			symbol = fmt[++i];
		    switch(symbol) {
		    	case 's':
					printed += prints(va_arg(arg, char *));
					break;
				case 'c':
					printed += printc(va_arg(arg, int));
					break;
				case 'd':
					printed += printn(va_arg(arg, int), _NUMBERS_BASE_DEC);
					break;
				case 'h':
					printed += printn(va_arg(arg, int), _NUMBERS_BASE_HEX);
					break;
				case 'b':
					printed += printn(va_arg(arg, int), _NUMBERS_BASE_BIN);
					break;
				case '%':
					printed += printc(symbol);
					break;
			}
		} else {
			printed += printc(fmt[i]);
		}

		i++;
	}

	return printed;
}
