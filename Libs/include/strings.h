#ifndef _LIB_STRINGS_H_
#define _LIB_STRINGS_H_

#define _STRINGS_CHAR_NOT_FOUND -1

unsigned int strlen(char * string);

/**
 * Compares 2 null terminated strings
 * @param  s1 a string
 * @param  s2 a string
 * @return    >0 if s1 is bigger, 0 if equal, <0 if smaller
 */
int strcmp(const char * s1, const char * s2);

/**
 * Copys the source string into destination
 * @param dest   a string
 * @param source a string
 */
void strcpy(char * dest, const char * source);

char * strnum(int value, int base, char * result);

int strfnd(const char * string, char character);

#endif