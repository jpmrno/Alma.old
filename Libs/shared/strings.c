#include <strings.h>
#include <stdint.h>

int strcmp(const char * s1, const char * s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++,s2++;
    }
    return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}

void strcpy(char * dest, const char * source) {
	int i = 0;

    while((dest[i] = source[i]) != '\0'){
    	i++;
    }
}

unsigned int intstr(int value, unsigned int base, char * buffer) { // TODO: Improve? Change?
    int shifter;
    unsigned int length = 0;

    if(value < 0) {
        *buffer++ = '-';
        value *= -1;
        length += 1;
    }

    return length + uintstr(value, base, buffer);
}

unsigned int uintstr(unsigned int value, unsigned int base, char * buffer) { // TODO: Improve? Change?
	char *p = buffer;
	char *p1, *p2;
	unsigned int digits = 0;

	//Calculate characters for each digit
	do {
		unsigned int remainder = value % base;
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
