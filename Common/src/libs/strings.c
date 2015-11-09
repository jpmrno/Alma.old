#include <strings.h>

#define CHAR_TO_INT(x)	((x)-'0')

int strcmp(const char * s1, const char * s2) {
    while(*s1 && (*s1 == *s2))
        s1++,s2++;
    return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}

void strcpy(char * dest, const char * source) {
	int i = 0;

    while ((dest[i] = source[i]) != '\0')
    	i++;
}

int strint(char * s, unsigned int * num) {	
	int length = 1;
	if (*s == 0 || *s == '\n') {
		*num = 0;
		return length;
	}

	int i = CHAR_TO_INT(*s);
	if (i < 0 || i > 9)
		return ERROR_NUMBER_NOT_POSITIVE;

	length = strint(s+1,num);
	if (length == ERROR_NUMBER_NOT_POSITIVE)
		return ERROR_NUMBER_NOT_POSITIVE;

	(*num) = (*num) + i*length;
	return length*10;
}