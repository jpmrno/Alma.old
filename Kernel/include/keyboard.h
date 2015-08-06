#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <define.h>

//ASCII CODE
#define ESC 0x1B

// Scan Codes source: http://stanislavs.org/helppc/make_codes.html
#define TAB 0x0F
#define LEFT_CONTROL  0x1D
#define LEFT_SHIFT  0x2A
#define RIGHT_SHIFT  0x36
#define LEFT_ALT  0x38
#define CAPS_LOCK  0x3A
#define NUM_LOCK 0x45
#define SCROLL_LOCK  0x46

#define FIRST_KEYPAD_CODE 0x47

#define KEY_PAD_0  0x52
#define KEY_PAD_1 0x4F 
#define KEY_PAD_2 0x50
#define KEY_PAD_3 0x51
#define KEY_PAD_4 0x4B
#define KEY_PAD_5 0x4C
#define KEY_PAD_6 0x4D
#define KEY_PAD_7 0x47
#define KEY_PAD_8 0x48
#define KEY_PAD_9 0x49
#define KEY_PAD_SUPR 0x53

#define FIRST_KEY_PAD_CODE KEY_PAD_7
#define LAST_KEY_PAD_CODE KEY_PAD_SUPR

#define F1  0x3B
#define F2  0x3C
#define F3  0x3D
#define F4  0x3E
#define F5  0x3F
#define F6  0x40
#define F7  0x41
#define F8  0x42
#define F9  0x43
#define F10 0x44
#define F11 0x57
#define F12 0x58

#define EXTENDED_SCAN_CODE 0xE0
#define ALTGR	0x38

#define KEYS_BUFFER_SIZE  256
#define MAX_CODE  0x53
#define KEYBOARD_BUFFER_FULL 1
#define KEYBOARD_BUFFER_EMPTY 0

#define NOT_PRINTABLE 0
#define PRINTABLE  1
#define FUNCTIONAL  2
#define NOT_CLASIFIED_FUNCTIONAL 3
#define RELEASED	4

typedef struct {
	int type;
	/**
	 * if type == PRINTABLE --> value is an ASCII code
	 * else --> value is the defined scanned code.
	 */
	char value;
} key_t;

/**
 * Buffers the given key into the key's buffer, at the corresponding position,
 * if there is enough free space to do so.
 * 
 * @param  key 		the key to be buffered.
 * @return     		OK if there was enough space to buffer the given key.
 *                  OtherWise, KEYBOARD_BUFFER_FULL is returned.
 *                  
 */
int keyboard_buffer(key_t *key);

/**
 * Removes from the keyboard's buffer the last inserted key if permitted.
 *
 * @return 	OK if the previous key could be cleaned.
 *          Otherwise, COULD_NOT_PERFORM_OPERATION is returned. 
 */
int keyboard_eraseLastCharacter();

/**
 * @return the next unread char from the key's buffer, if there is one.
 */
char keyboard_getChar();

/**
 * 
 * @return 		TRUE if the buffer can be read 
 *              (at least one enter has been buffered).
 *              FALSE otherwise.
 */
int keyboard_canRead();

/**
 * Changes the keyboard keys distribution.
 * If SPANISH_KEYBOARD --> ENGLISH_KEYBOARD
 * If ENGLISH_KEYBOARD --> SPANISH_KEYBOARD
 */
void keyboard_changeKeyboard();

#endif