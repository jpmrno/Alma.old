#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "define.h"
#include "shell.h"
#include "libc.h"
#include "time.h"

// Commands vector size
#define CMDS_SIZE 10

// Time
#define MAX_TIME_NUM_LENGTH 10
#define TIME_T_FIELDS 6
// Screensaver
#define MAX_SCREEN_SAVER_TIME_LENGTH (3 + 1)
#define MAX_TERMINAL_NUM_LENGTH (1 + 1)
// Terminal
#define MAX_COLOR_LENGTH (2 + 1)

// Command type definition
typedef struct {
	char * name;
	int (*func)();
	char * help;
} tCommand;

/**
 * Changes the user's name
 * @return OK if only one argument was written and could change the user's name
 *           or returns error code if name is too long o another error occurred
 */
int cmd_user();

/**
 * Prints the lists of commands in case no argument was written
 * Prints a command's help if only one argument was written
 * @return OK if command exists or error code if not or if too many arguments
 *            written
 */
int cmd_help();

/**
 * Prints time if no arguments were written or if argument "get" is written
 * Changes time if arguments "set <values>" were written
 * @return OK if amount of arguments written are ok or error code if wrong
 *            or missing arguments
 */
int cmd_time();

/**
 * Sets screensaver options
 * Changes screensaver's time if argument time and number were written
 * Enables or disables the screensaver if enable or disable argument was 
 * written
 * @return OK if operation finished ok or error code if arguments were invalid
 *            or missing
 */
int cmd_screensaver();

/**
 * Sets terminal options
 * Changes text or background color if arguments background or text were
 * written
 * Changes current terminal if arguments "set <number>" were writen
 * Clears screen if parameter "clear" was written
 * @return OK if arguments passed are valid and operation finished ok or error
 *            code otherwise
 */
int cmd_terminal();

/**
 * Clears the screen
 * @return OK if no other argument was written or error code otherwise
 */
int cmd_clear();

/**
 * Changes the terminal text color
 * @return OK if a valid color number or error code if argument missing or 
 *            invalid
 */
int cmd_text();

/**
 * Changes the terminal background color
 * @return OK if a valid color number or error code if argument missing or 
 *            invalid
 */
int cmd_background();

#endif