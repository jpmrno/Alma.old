#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_

#include <colors.h>
#include <define.h>

#define VIDEO_ROWS 25
#define VIDEO_COLUMNS 80
#define VIDEO_SIZE (VIDEO_ROWS * VIDEO_COLUMNS * 2)

#define ERROR_POSITION_INVALID -1

/**
 * Initialize the screen, by clearing all the existent data,
 * making the cursor enable, and reseting its position to the
 * beginning of the screen.
 */
void initVideo();

/**
 * Writes the given character at the corresponding position of the screen.
 * @param character			 the character to be written
 */
void write(char character);

/**
 * Writes the given character at the given position.
 * @param  character			the character to be written
 * @param  position 			the position where to write the character
 * @return          			OK if the position is valid.
 *                        		ERROR_POSITION_INVALID otherwise.
 */
int put(char character, unsigned int position);

/**
 * Writes the given style at the given position.
 * @param  thisStyle 			the style to be written
 * @param  position  			the position where to write the character
 * @return           			OK if the position is valid.
 *                        		ERROR_POSITION_INVALID otherwise.
 */
int putStyleOf(uint8_t thisStyle, unsigned int position);

/**
 * Gets the character at the given position
 * @param  position 			the position from where to get the character
 * @return          			the character at the given position, if valid.
 *                         		ERROR_POSITION_INVALID otherwise.
 */
uint8_t get(unsigned int position);

/**
 * Gets the style at the given position
 * @param  position 			the position from where to get the style
 * @return          			the style at the given position, if valid.
 *                         		ERROR_POSITION_INVALID otherwise.
 */
uint8_t getStyleOf(unsigned int position);

/**
 * Sets the cursor at the given position and updates it.
 * @param  position  			the position where to set the cursor
 * @return           			OK if the position is valid.
 *                        		ERROR_POSITION_INVALID otherwise.
 */
int setCursor(unsigned int position);

/**
 * 
 * @return the cursor position
 */
unsigned int getCursor();

/**
 * Inserts a new line in the screen, from the cursor's position.
 * Note that everything following the cursor's line position will be deleted.
 * So, for using this function, be sure that the cursor is after the last
 * inserted character.
 */
void newLine();

/**
 * Deletes the last inserted character & style.
 */
void delete();

/**
 * Clears the screen, reseting the cursor's position 
 * to the beginning of the screen.
 */
void clearAll();

/**
 * Sets the default style to the whole screen.
 */
void clearStyle();

/**
 * Sets the given style to the whole screen.
 * @param newStyle				the style to be set
 */
void styleAll(uint8_t newStyle);

/**
 * Sets the given color to the whole screen.
 * @param color 				the color to be set
 */
void colorAll(uint8_t color);

/**
 * Sets the given background to the whole screen.
 * @param background 			the background to be set
 */
void backgroundAll(uint8_t background);

/**
 * Sets the active style to the default one
 * for the next writings
 */
void restoreStyle();

/**
 * Sets the active style to the given one
 * for the next writings
 * @param newStyle			the style to be set
 */
void setStyle(uint8_t newStyle);

/**
 * @return  				the active style
 */
uint8_t getStyle();

/**
 * Sets the active color to the given one
 * for the next writings
 * @param color 			the color to be set
 */
void setColor(uint8_t color);

/**
 * Sets the active background to the given one
 * for the next writings
 * @param background 		the background to be set
 */
void setBackground(uint8_t background);

/**
 * // TODO: 
 * @param enabled [description]
 */
void showCursor(int enabled)

#endif
