#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <colors.h>
#include <define.h>

#define ERROR_SCREEN_INVALID -1

/**
 * Locks the current screen so as to avoid deleting what 
 * has been already written
 * @return   		OK if opperation could be performed
 */
int terminal_lockCurrentScreen();

/**
 * Initialize all the terminals.
 */
void initTerminal();

/**
 * Deletes all characters from the screen.
 */
void clearScreen();

/**
 * Backups the current terminal and sets the new one, given by the index.
 * This is done by associating the screen to the terminal that mathces
 * the given index.
 * @param  index			the index of the desired terminal 
 * @return       			OK if there is a terminal matching the given index.
 *                     		ERROR_SCREEN_INVALID otherwise.
 */
int setScreen(unsigned int index);

/**
 * Starts the screen saver.
 */
void screenSaver_start();

/**
 * Stops the screen saver.
 */
void screenSaver_stop();

/**
 * Prints to the screen the given string
 * @param  string 				the string to be printed   
 * @return        				how many characters were printed
 */	
int print(const char * string);

/**
 * Prints a new line to the screen
 */
void println();

/**
 * Prints the given character to the screen.
 * @param character   			the character to be printed.
 */	
void printChar(char character);

/**
 * Prints the given positive integer to the screen.
 * @param value 		the integer to be printed
 */
void printInt(uint64_t value);

/**
 * Prints the given hexa number to the screen.
 * @param value 		the hexa number to be printed
 */
void printHex(uint64_t value);

/**
 * Prints the given binary number to the screen.
 * @param value 		the binary number to be printed
 */
void printBin(uint64_t value);

/**
 * +++xdocument
 */
void setTerminalColor(uint8_t color);
void setTerminalBackground(uint8_t color);

#endif