#ifndef _LIB_STDIO_H_
#define _LIB_STDIO_H_

#include <define.h>
#include <sys_io.h>

#define EOF -1

/**
 * Reads one character from the standard input.
 * @return         - the read character or EOF if end of file.
 */
int getchar();

/**
 * Reads input until it finds a space character, a new line character, 
 * EOF symbol or buffer is full.
 * @param  buffer  - where to save what it is read
 * @param  maxSize - the maximum size of the buffer. The amount of letters
 *                 	 that will be read is maxSize-1 to complete last position
 *                 	 with the correspondig '\0' character.
 * @return         - the length of the line read, including the '\0'
 *                   additional character.
 */
int scanf(char * buffer, int maxSize);

/**
 * Reads input until it finds a space character, a new line character, 
 * EOF symbol or buffer is full.
 * Note that the buffer will not be automatically NULL-TERMINATED.
 * 
 * @param  buffer  - where to save what it is read
 * @param  maxSize - the maximum size of the buffer.
 * @return         - the length of the line read without the end character.
 */
int scanw(char * buffer, int maxSize);

/**
 * Writes the string pointed by fmt to the standard output
 * If fmt includes format specifiers (subsequences beginning with %), the 
 * additional arguments following format are formatted and inserted in the 
 * resulting string replacing their respective specifiers.
 *
 * @param fmt the format sctring with or without format sprecifiers
 * @return caracters of fmt read
 */
uint64_t printf(char * fmt, ...);

/**
 * Writes a single char to the standart output
 * @param  character	the character to be written
 * @return  1 if caracter was written correctly, 0 otherwise
 */
uint64_t putChar(char character);

/**
 * Writes the string to the standart output
 * @param  string	the string to be written
 * @return	the number of characters written
 */
uint64_t putString(char * string);

/**
 * Writes the string representation of the number to the standart output
 * @param  num	the number to be written
 * @return	the number of characters of the representation if the number written
 */
uint64_t putInt(int num);

#endif