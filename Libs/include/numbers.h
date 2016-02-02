#ifndef _LIB_NUMBERS_H_
#define _LIB_NUMBERS_H_

#define _NUMBERS_ERROR_NUMBER_NOT_POSITIVE -1

#define _NUMBERS_BASE_BINARY 2
#define _NUMBERS_BASE_DECIMAL 10
#define _NUMBERS_BASE_HEXADECIMAL 16

/**
 * Converts a string into a number only if the number is possitive
 * @param  s   the string
 * @param  num the return value for the number
 * @return     the length of the number or <0 if error occurred
 */
int strint(const char * s, unsigned int * num);

#endif