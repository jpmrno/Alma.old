#include <io.h>
#include <primitives.h>
#include <limits.h>

#define CONVERTER_BUFFER_SIZE 128

#define BASE_BINARY 2
#define BASE_HEXADECIMAL 16
#define BASE_DECIMAL 10

// Convert buffer
static char buffer[CONVERTER_BUFFER_SIZE] = {0};

/**
 * Writes a number in desired base into standart output
 * @param value 	the number
 * @param base 		the number's base
 * @return 			# of characters of the string that represents the 
 *                  desired number written
 */
static uint64_t putInBase(uint64_t value, uint32_t base);

/**
 * Converts a number to a desired base and generates the string that represents
 * the number converted
 * @param  value  the number
 * @param  buffer were to write the string
 * @param  base   the number's base
 * @return        # of digits of the number
 */
static unsigned int uintToBase(uint64_t value, char * buffer, uint32_t base);

static uint64_t putInBase(uint64_t value, uint32_t base) {
	int ret = uintToBase(value, buffer, base);
	return write(buffer, ret);
}

static unsigned int uintToBase(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do {
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

int getchar() {
	char c;
	int ret = read(&c, 1);
	if (ret != EOF) {
		ret = c;
	}
	return ret;
}

int scanf(char * buffer, int maxSize) {
	int length = scanw(buffer,maxSize);
	buffer[length] = 0;
	return length;
}

int scanw(char * buffer, int maxSize) {
	int c;
	int i = 0; // points to the next position where to insert
	do
	{
		c = getchar();
		if (c != EOF)
		{
			buffer[i++] = c;
		}
	}
	while (c != ' ' && c != '\n' && c != 0 && c != EOF && i<maxSize);
	return i - 1;
}

uint64_t printf(char * fmt, ...) {
    char symbol;
    int i = 0;
    va_list arg;

    va_start(arg, fmt);
    while(fmt[i] != 0) {
		if(fmt[i] == '%') {
			symbol = fmt[++i];
		    switch(symbol) {
		    	case 's':
					putString(va_arg(arg, char *));
					break;
				case 'c':
					putChar(va_arg(arg, int));
					break;
				case 'd':
					putInt(va_arg(arg, int));
					break;
				case 'x':
					putInBase(va_arg(arg, unsigned int), BASE_HEXADECIMAL);
					break;
				case 'b':
					putInBase(va_arg(arg, unsigned int), BASE_BINARY);
					break;
				case '%':
					putChar(symbol);
					break;
		    }
		} else {
			putChar(fmt[i]);
		}
		i++;
    }
    va_end(arg);

    return i - 1;
}

uint64_t putChar(char character) {
	return write(&character, 1);
}

uint64_t putString(char * string) {
	return write(string, UINT_MAX);
}

uint64_t putInt(int num) {
	return putInBase(num, BASE_DECIMAL);
}
