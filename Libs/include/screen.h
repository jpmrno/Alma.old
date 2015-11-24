#ifndef _LIB_SCREEN_H_
#define _LIB_SCREEN_H_

#include <define.h>
#include <sys_screen.h>

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

int settScreenSaver(int enabled, char * text, int seconds, int loop);

#endif