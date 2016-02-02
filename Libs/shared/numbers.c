#include <numbers.h>

#define CHAR_TO_INT(x)	((x)-'0')

int strint(const char * s, unsigned int * num) {	
	int length = 1;
	if (*s == 0 || *s == '\n') {
		*num = 0;
		return length;
	}

	int i = CHAR_TO_INT(*s);
	if (i < 0 || i > 9) {
		return _NUMBERS_ERROR_NUMBER_NOT_POSITIVE;
	}

	length = strint(s + 1, num);
	if (length == _NUMBERS_ERROR_NUMBER_NOT_POSITIVE) {
		return _NUMBERS_ERROR_NUMBER_NOT_POSITIVE;
	}

	(*num) = (*num) + i * length;

	return length * 10;
}