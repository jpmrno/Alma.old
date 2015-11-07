#ifndef _SHELL_H_
#define _SHELL_H_

#include <define.h>
#include <io.h>
#include <commands.h>

#define MAX_BUFFER_LENGTH 128
#define MAX_USER_NAME (10 + 1)

#define OK 0
#define ERROR -1
#define ERROR_CMD_EMPTY -2
#define ERROR_CMD_INVALID -3
#define ERROR_ARGUMENTS_MISSING -4
#define ERROR_ARGUMENTS_EXCESS -5
#define ERROR_ARGUMENTS_INVALID -6

/**
 * Gets the word from STDOUT, null terminates it and sets hasMoreArgs to FALSE 
 * if it ended in '\n' or FALSE otherwise and sets completelyReadWord to TRUE
 * if it ended with '\n' or ' ' or to FALSE otherwise
 * @param  cmd 	where to write whats read
 * @param  max 	max length to read
 * @return     	length read
 */
int getWord(char * cmd, int max);

/**
 * Prints the error msj represented by error number
 * @param error the error number
 */
void printError(int error);

#endif