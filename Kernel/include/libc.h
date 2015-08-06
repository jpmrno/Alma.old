#ifndef _LIB_C_H_
#define _LIB_C_H_

#include <stdint.h>

/**
 * Fills the destination with the given character, the given length
 * @param  destination - where to write the character
 * @param  character   - the character to be written
 * @param  length      - the expected amount of characters to be written
 * @return             - the amount of characters really written
 */
void * memset(void * destination, int32_t character, uint64_t length);

/**
 * Copies from source to desttination, length characters.
 * @param  destination - where to copy the characters
 * @param  source      - from where to copy the characters
 * @param  length      - the expected amount of characters to be copied
 * @return             - the amount of characters really copied
 */
void * memcpy(void * destination, const void * source, uint64_t length);

/**
 * Clears the memory segment starting at bssAddress and of bssSize size
 * @param bssAddress - the starting position of the memory segment
 * @param bssSize    - the size of the memory segment
 */
void clearBSS(void * bssAddress, uint64_t bssSize);
#endif