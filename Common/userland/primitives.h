#ifndef _SYS_CALLERS_H_
#define _SYS_CALLERS_H_

#include <define.h>
#include <syscalls.h>

/**
 * Write SDTOUT syscall
 * Attempts to write up to length bytes from the buffer pointed bufffer to 
 * STDOUT.
 * @param  buffer 	the string to be written
 * @param  length 	the length if the string
 * @return        	the characters of the screen that were written
 */
int write(char * buffer, int length);

/**
 * Read STDIN syscall
 * Attempts to read up to length bytes from STDIN into the buffer starting 
 * at buffer
 * @param  buffer 	the string
 * @param  length 	the length of the string
 * @return        	the characters of the string that were read
 */
int read(char * buffer, int length);

/**
 * Clears the terminal screen
 * @return   OK if could clean, !OK otherwise
 */
int terminal_clear();

/**
 * Changes the current terminal
 * @param  index the number that represents the terminal wanted
 * @return       OK if index is ok or error code otherwise
 */
int terminal_set(int index);

/**
 * Changes the terminal text if text > 0 or background color otherwise
 * @param  text  >1 if text color or 0 if background color
 * @param  color the color representation
 * @return       OK if the operation finished ok, error code otherwise
 */
int terminal_color(unsigned int text, unsigned char color);

/**
 * Reads the date and time from the RTC, and stores the data at t
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int time_read(tSystemTime * t);

/**
 * Writes the data of the given t at the RTC
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int time_write(tSystemTime * t);

/**
 * // TODO: Docs
 * @param  enabled [description]
 * @param  text    [description]
 * @param  seconds [description]
 * @param  loop    [description]
 * @return         [description]
 */
int screensaver_set(int enabled, char * text, int seconds, int loop);

/**
 * Enables or disables the screen saver
 * @param  boolean >0 enables, otherwise disable
 * @return         OK if process could be completed
 *                 !OK otherwise
 */
int screensaver_enabled(unsigned int boolean);

/**
 * Sets the screensaver activation time
 * @param  seconds the time needs to pass before screensaver activates
 * @return         OK if process could be completed, error code if otherwise
 */
int screensaver_time(int seconds);

#endif