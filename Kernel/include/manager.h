#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <define.h>

/**
 * Reads count or less characters from the standard input,
 * and stores them at the given buffer.
 * @param  buffer where to save the read characters
 * @param  count the amount of letters that will be read.
 * @return        how many characters were read; -1 if error.
 */
int manager_readSTDIN(char *buffer, unsigned int count);

/**
 * Writes to the screen the given string of the given length
 * @param  string 				the string to be written   
 * @param  length 				the length of the string
 * @return        				how many characters were really written
 */		
int manager_writeSTDOUT(const char * string, unsigned int length);

/**
 * Clears the current terminal screen.
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
int manager_clearScreen();

/**
 * Sets the terminal identified by the given index
 * @param  index - 	the index that identifies the desired terminal to be set
 * @return       	OK if there is a terminal matching the given index.
 *                  ERROR_SCREEN_INVALID otherwise.
 */
int manager_setTerminal(unsigned int index);

/**
 * Sets the given color for all the current terminal's screen.
 * If text param is not equal to 0, then the color is applied to
 * the text. Else, it is applied to the background.
 * @param  text  - 	whether to apply the color to the text ( != 0 ) 
 *               	or to the background ( == 0)
 * @param  color - 	the desired color to be applied
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
int manager_setColor(int text, uint8_t color);

/**
 * Enables / Disables the screen saver, depending on the value given by enabled
 * If enabled != 0 --> the screensaver is enabled
 * If enabled == 0 --> the screensaver is disabled
 * @param  enabled - whether to enable ( != 0 ) or disable ( == 0 ) 
 *                 	 the screensaver
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
int manager_setScreenSaverEnabled(int enabled);

/**
 * Sets how many seconds the system will wait to display the screensaver
 * @param  seconds - the time, in seconds, to display the screensaver
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
int manager_setScreenSaverTime(uint16_t seconds);

int manager_setScreenSaver(int enabled, char * text, int seconds, int loop);

#endif