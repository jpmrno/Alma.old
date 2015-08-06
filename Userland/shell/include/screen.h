#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <define.h>

#define MIN_SCREENSAVER_TIME 5

#define ERROR_SCREENSAVER_TIME -1

#define MIN_TERMINAL 1
#define MAX_TERMINAL 2
#define MIN_COLOR 0x0
#define MAX_COLOR 0xF

#define ERROR_INVALID_TERMINAL -2
#define ERROR_INVALID_COLOR -3

/**
 * Clears the terminal screen
 */
void clearScreen();

/**
 * Changes the current terminal
 * @param  index the number that represents the terminal wanted
 * @return       OK if index is ok or error code otherwise
 */
int setTerminal(int index);

/**
 * Changes the terminal text color
 * @param  color the color representation
 * @return       OK if the operation finished ok, error code otherwise
 */
int setTerminalTextColor(unsigned char color);

/**
 * Changes the terminal background color
 * @param  color the color representation
 * @return       OK if the operation finished ok, error code otherwise
 */
int setTerminalBackgroundColor(unsigned char color);

/**
 * Sets the screensaver activation time
 * @param  seconds the time needs to pass before screensaver activates
 * @return         OK if process could be completed, error code if otherwise
 */
int setScreenSaverTime(int seconds);

/**
 * Enables the screen saver
 */
void enableScreenSaver();

/**
 * Disables the screen saver
 */
void disableScreenSaver();

#endif