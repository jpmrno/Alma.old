#include <keyboard.h>

#define KEYBOARDS	2
#define KEYS_ENTRIES 91
#define KEYS_ALTERNATIVES 3

#define SPANISH_KEYBOARD 0
#define ENGLISH_KEYBOARD 1

static int currentKeyboard = SPANISH_KEYBOARD;
static key_t keyBuffer[KEYS_BUFFER_SIZE];
static int entersCounter = 0;
static int nextInsert = 0;
static int lastReturn = KEYS_BUFFER_SIZE-1;
static int ctrlPressed = FALSE;
static int shiftPressed = FALSE;
static int altPressed = FALSE;
static int altgrPressed = FALSE;
static int capsEnable = FALSE;
static int keyPadEnable = TRUE;
static int waitingExtendedScanncode = FALSE;

/**
 * [Copied from its definition at: manager.c]
 * Recieves a key pointer and decides what action to perform, 
 * depending on the manager's flag status and the kind of key it is.
 *
 * IMPORTANT: This function should be only used by the keybardHandler function
 * at: keyboard.c. That's why its declaration is not included at: manager.h
 * @param key - the key to decide which action to perform
 */
void manager_keyReceived(key_t *key);

/**
 * Modified from: from previous years tpes
 */
static unsigned char keys[KEYBOARDS][KEYS_ENTRIES][KEYS_ALTERNATIVES] = {
{	// SPANISH_KEYBOARD
	{ NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*000*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*001 ESCAPE*/
    { '1', '!', NOT_PRINTABLE }, /*002*/
    { '2', '\"', '@' }, /*003*/
    { '3', '#', NOT_PRINTABLE }, /*004*/
    { '4', '$', NOT_PRINTABLE }, /*005*/
    { '5', '%', NOT_PRINTABLE }, /*006*/
    { '6', '&', NOT_PRINTABLE }, /*007*/
    { '7', '/', NOT_PRINTABLE }, /*008*/
    { '8', '(', NOT_PRINTABLE }, /*009*/
    { '9', ')', NOT_PRINTABLE }, /*010*/
    { '0', '=', NOT_PRINTABLE }, /*011*/
    { '\'', '?', NOT_PRINTABLE }, /*012*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*013*/
    { '\b', '\b', NOT_PRINTABLE }, /*014 BACKSPACE*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*015 TAB*/
    { 'q', 'Q', NOT_PRINTABLE }, /*016*/
    { 'w', 'W', NOT_PRINTABLE }, /*017*/
    { 'e', 'E', NOT_PRINTABLE }, /*018*/
    { 'r', 'R', NOT_PRINTABLE }, /*019*/
    { 't', 'T', NOT_PRINTABLE }, /*020*/
    { 'y', 'Y', NOT_PRINTABLE }, /*021*/
    { 'u', 'U', NOT_PRINTABLE }, /*022*/
    { 'i', 'I', NOT_PRINTABLE }, /*023*/
    { 'o', 'O', NOT_PRINTABLE }, /*024*/
    { 'p', 'P', NOT_PRINTABLE }, /*025*/
    { '`', '^', NOT_PRINTABLE }, /*026*/
    { '+', '*', NOT_PRINTABLE }, /*027*/
    { '\n', '\n', '\n' }, /*028*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*029 CTRL IZQ*/
    { 'a', 'A', NOT_PRINTABLE }, /*030*/
    { 's', 'S', NOT_PRINTABLE }, /*031*/
    { 'd', 'D', NOT_PRINTABLE }, /*032*/
    { 'f', 'F', NOT_PRINTABLE }, /*033*/
    { 'g', 'G', NOT_PRINTABLE }, /*034*/
    { 'h', 'H', NOT_PRINTABLE }, /*035*/
    { 'j', 'J', NOT_PRINTABLE }, /*036*/
    { 'k', 'K', NOT_PRINTABLE }, /*037*/
    { 'l', 'L', NOT_PRINTABLE }, /*038*/
    { ':', ';', NOT_PRINTABLE }, /*039*/
    { '{', '[', NOT_PRINTABLE }, /*040*/
    { '\\', '\\', NOT_PRINTABLE }, /*041*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*042 SHIFT IZQ*/
    { '}', ']', NOT_PRINTABLE }, /*043*/
    { 'z', 'Z', NOT_PRINTABLE }, /*044*/
    { 'x', 'X', NOT_PRINTABLE }, /*045*/
    { 'c', 'C', NOT_PRINTABLE }, /*046*/
    { 'v', 'V', NOT_PRINTABLE }, /*047*/
    { 'b', 'B', NOT_PRINTABLE }, /*048*/
    { 'n', 'N', NOT_PRINTABLE }, /*049*/
    { 'm', 'M', NOT_PRINTABLE }, /*050*/
    { ',', ';', NOT_PRINTABLE }, /*051*/
    { '.', ':', NOT_PRINTABLE }, /*052*/
    { '-', '_', '/' }, /*053*/ /* / */
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*054 SHIFT DER*/
    { '*', '*', NOT_PRINTABLE}, /*055 KEY **/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*056 ALT IZQ*//* ALT DER*/
    { ' ', ' ', NOT_PRINTABLE }, /*057 SPACE*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*058 CAPSLOCK*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*059 F1*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*060 F2*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*061 F3*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*062 F4*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*063 F5*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*064 F6*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*065 F7*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*066 F8*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*067 F9*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*068 F10*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*069 NUM LOCK*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*070 SCROLL LOCK*/
    { NOT_PRINTABLE, '7', NOT_PRINTABLE }, /*071 KEY 7*/ /* inicio */
    { NOT_PRINTABLE, '8', NOT_PRINTABLE },/*072 KEY 8*//* flecha para arriba */
    { NOT_PRINTABLE, '9', NOT_PRINTABLE }, /*073 KEY 9*/ /* repag */
    { '-', '-' , NOT_PRINTABLE}, /*074 KEY -*/
    { NOT_PRINTABLE, '4', NOT_PRINTABLE },/*075 KEY 4*//* flecha para la izq */
    { NOT_PRINTABLE, '5', NOT_PRINTABLE }, /*076 KEY 5*/
    { NOT_PRINTABLE, '6', NOT_PRINTABLE },/*077 KEY 6*//* flecha para la der */
    { '+', '+', NOT_PRINTABLE }, /*078 KEY +*/
    { NOT_PRINTABLE, '1', NOT_PRINTABLE }, /*079 KEY 1*/ /* fin */
    { NOT_PRINTABLE, '2', NOT_PRINTABLE }, /*080 KEY 2*/ /* flecha para abajo */
    { NOT_PRINTABLE, '3', NOT_PRINTABLE }, /*081 KEY 3*/ /* avpag */
    { NOT_PRINTABLE, '0', NOT_PRINTABLE }, /*082 KEY 0*/ /* insert */
    { NOT_PRINTABLE, '.', NOT_PRINTABLE }, /*083 KEY .*/ /* supr */
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*084 SYS REQ (AT)*/
    { '+', '*', NOT_PRINTABLE }, /*085*/
    { '<', '>', NOT_PRINTABLE }, /*086*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*087 F11*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*088 F12*/
    { '+', '*', NOT_PRINTABLE }, /*089*/
    { '+', '*', NOT_PRINTABLE } /*090*/
},
{ 	// ENGLISH_KEYBOARD
	{ NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*000*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*001 ESCAPE*/
    { '1', '!', NOT_PRINTABLE }, /*002*/
    { '2', '@', NOT_PRINTABLE }, /*003*/
    { '3', '#', NOT_PRINTABLE }, /*004*/
    { '4', '$', NOT_PRINTABLE }, /*005*/
    { '5', '%', NOT_PRINTABLE }, /*006*/
    { '6', '^', NOT_PRINTABLE }, /*007*/
    { '7', '&', NOT_PRINTABLE }, /*008*/
    { '8', '*', NOT_PRINTABLE }, /*009*/
    { '9', '(', NOT_PRINTABLE }, /*010*/
    { '0', ')', NOT_PRINTABLE }, /*011*/
    { '-', '_', NOT_PRINTABLE }, /*012*/
    { '=', '+', NOT_PRINTABLE }, /*013*/
    { '\b', '\b', NOT_PRINTABLE }, /*014 BACKSPACE*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*015 TAB*/
    { 'q', 'Q', NOT_PRINTABLE }, /*016*/
    { 'w', 'W', NOT_PRINTABLE }, /*017*/
    { 'e', 'E', NOT_PRINTABLE }, /*018*/
    { 'r', 'R', NOT_PRINTABLE }, /*019*/
    { 't', 'T', NOT_PRINTABLE }, /*020*/
    { 'y', 'Y', NOT_PRINTABLE }, /*021*/
    { 'u', 'U', NOT_PRINTABLE }, /*022*/
    { 'i', 'I', NOT_PRINTABLE }, /*023*/
    { 'o', 'O', NOT_PRINTABLE }, /*024*/
    { 'p', 'P', NOT_PRINTABLE }, /*025*/
    { '[', '{', NOT_PRINTABLE }, /*026*/
    { ']', '}', NOT_PRINTABLE }, /*027*/
    { '\n', '\n', '\n' }, /*028*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*029 CTRL IZQ*/
    { 'a', 'A', NOT_PRINTABLE }, /*030*/
    { 's', 'S', NOT_PRINTABLE }, /*031*/
    { 'd', 'D', NOT_PRINTABLE }, /*032*/
    { 'f', 'F', NOT_PRINTABLE }, /*033*/
    { 'g', 'G', NOT_PRINTABLE }, /*034*/
    { 'h', 'H', NOT_PRINTABLE }, /*035*/
    { 'j', 'J', NOT_PRINTABLE }, /*036*/
    { 'k', 'K', NOT_PRINTABLE }, /*037*/
    { 'l', 'L', NOT_PRINTABLE }, /*038*/
    { ';', ':', NOT_PRINTABLE }, /*039*/
    { '\'', '\"', NOT_PRINTABLE }, /*040*/
    { '`', '~', NOT_PRINTABLE }, /*041*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*042 SHIFT IZQ*/
    { '\\', '|', NOT_PRINTABLE }, /*043*/
    { 'z', 'Z', NOT_PRINTABLE }, /*044*/
    { 'x', 'X', NOT_PRINTABLE }, /*045*/
    { 'c', 'C', NOT_PRINTABLE }, /*046*/
    { 'v', 'V', NOT_PRINTABLE }, /*047*/
    { 'b', 'B', NOT_PRINTABLE }, /*048*/
    { 'n', 'N', NOT_PRINTABLE }, /*049*/
    { 'm', 'M', NOT_PRINTABLE }, /*050*/
    { ',', '<', NOT_PRINTABLE }, /*051*/
    { '.', '>', NOT_PRINTABLE }, /*052*/
    { '/', '?', '/' }, /*053*/ /* / */
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*054 SHIFT DER*/
    { '*', '*', NOT_PRINTABLE}, /*055 KEY **/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*056 ALT IZQ*//* ALT DER*/
    { ' ', ' ', NOT_PRINTABLE }, /*057 SPACE*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*058 CAPSLOCK*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*059 F1*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*060 F2*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*061 F3*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*062 F4*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*063 F5*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*064 F6*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*065 F7*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*066 F8*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*067 F9*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*068 F10*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*069 NUM LOCK*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE }, /*070 SCROLL LOCK*/
    { NOT_PRINTABLE, '7', NOT_PRINTABLE }, /*071 KEY 7*/ /* inicio */
    { NOT_PRINTABLE, '8', NOT_PRINTABLE },/*072 KEY 8*//* flecha para arriba */
    { NOT_PRINTABLE, '9', NOT_PRINTABLE }, /*073 KEY 9*/ /* repag */
    { '-', '-' , NOT_PRINTABLE}, /*074 KEY -*/
    { NOT_PRINTABLE, '4', NOT_PRINTABLE },/*075 KEY 4*//* flecha para la izq */
    { NOT_PRINTABLE, '5', NOT_PRINTABLE }, /*076 KEY 5*/
    { NOT_PRINTABLE, '6', NOT_PRINTABLE },/*077 KEY 6*//* flecha para la der */
    { '+', '+', NOT_PRINTABLE }, /*078 KEY +*/
    { NOT_PRINTABLE, '1', NOT_PRINTABLE }, /*079 KEY 1*/ /* fin */
    { NOT_PRINTABLE, '2', NOT_PRINTABLE }, /*080 KEY 2*/ /* flecha para abajo */
    { NOT_PRINTABLE, '3', NOT_PRINTABLE }, /*081 KEY 3*/ /* avpag */
    { NOT_PRINTABLE, '0', NOT_PRINTABLE }, /*082 KEY 0*/ /* insert */
    { NOT_PRINTABLE, '.', NOT_PRINTABLE }, /*083 KEY .*/ /* supr */
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*084 SYS REQ (AT)*/
    { '+', '*', NOT_PRINTABLE }, /*085*/
    { '\\', '|', NOT_PRINTABLE }, /*086*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*087 F11*/
    { NOT_PRINTABLE, NOT_PRINTABLE, NOT_PRINTABLE },/*088 F12*/
    { '+', '*', NOT_PRINTABLE }, /*089*/
    { '+', '*', NOT_PRINTABLE } /*090*/
}

};



/**
 * Processes the given scanned code, transforming it into a
 * key that the sytem will use for future purposes.
 * @param  scannedCode		the scanned code 
 * @return             		the key with the information obtained
 *                          since the given scanned code.
 */
static key_t process(unsigned char scannedCode);

/**
 * Returns TRUE if the given scan code is mapped to a functional key
 * and performs the necessary actions with the information given by 'pressed'.
 * 
 * @param  c       		the scan code to be checked
 * @param  pressed 		wheter the key with the given scan code has been
 *                   	pressed (pressed==TRUE) or released (pressed==FALSE)
 * @return         		TRUE if the given scan code is mapped to a 
 *                      functional key.
 *                      FALSE otherwise.
 */
static int isFunctional(unsigned char c, int pressed);


/**
 * Gets the ascii code of the given scan code.
 * 
 * This ascii code is taken from the keys matrix,
 * and depends on all the conext's flags status.
 * 
 * If no ascii value is associated with the given scan code,
 * NOT_PRINTABLE constant is returned.
 * 
 * @param  c 		the scan code
 * @return   		the ascii value associated with the	given scan code
 *                  (it depends on context's flags status).
 */
static int getAsciiCode(unsigned char c);

/**
 * 
 * @param  c 	the ascii to be checked
 * @return    	TRUE if c corresponds to an alphabetic ascii character
 *              FALSE otherwise 
 */
static int isAlpha(unsigned char c);

/**
 * 
 * @param  c 	the scan code to be checked
 * @return    	TRUE if c corresponds to a key pad scan code
 *              FALSE otherwise 
 */
static int isKeyPadKey(unsigned char c);


/**
 * Receives a scan code and process it, performing the necessary actions
 * to keep track of what has been done with the keyboard, and the key's buffer.
 *  
 * @param  scannedCode		the scan code to process
 * @returned             	OK if there was no problem while processing
 *                        	the scanned Code.
 *                        	COULD_NOT_PERFORM_OPERATION otherwise.
 */
int keyboardHandler(unsigned char scannedCode)
{ 
	key_t key;
	key = process(scannedCode);

	manager_keyReceived(&key);

	return OK;
}

int keyboard_buffer(key_t *key)
{

	int nextOfNext = nextInsert+1 >= KEYS_BUFFER_SIZE ? 0 : nextInsert+1;
	/*
	 * Asks this way because, when writing the expected '\n' key,
	 * there will be (nextInsert = nextOfNext) == lastReturned.
	 * 
	 * If it was asking nextInsert == lastReturn, then it would be
	 * (nextInsert = nextOfNext) == nextReturn, and getchar() would be
	 * returning KEYBOARD_BUFFER_EMPTY, and this is not the case.
	 */
	if (nextOfNext == lastReturn)
	{
		if (key->value != '\n')
		{
			return KEYBOARD_BUFFER_FULL;	
		}	
	}

	if (key->type != PRINTABLE)
	{
		return INVALID_KEY;
	}

	if (key->value == '\n')
	{
		entersCounter++;
	}	

	keyBuffer[nextInsert] = *key;
	nextInsert = nextOfNext;
	return OK;
}


int keyboard_eraseLastCharacter()
{
	/*
	 * Simulates the erasure of the previous key so as not to left the
	 * buffer inconsistent in case an interrupt changes the buffer state.
	 */
	int prevInsert = nextInsert-1 == -1 ? KEYS_BUFFER_SIZE-1 : nextInsert-1 ;

	if (prevInsert == lastReturn)
	{
		return COULD_NOT_PERFORM_OPERATION;
	}

	if (keyBuffer[prevInsert].value != '\n')
	{
		nextInsert = prevInsert;
		return OK;
	}
	
	return COULD_NOT_PERFORM_OPERATION;
}

char keyboard_getChar()
{
	int c = 0;

	int nextReturn = lastReturn+1 >= KEYS_BUFFER_SIZE ? 0 : lastReturn+1;

	if (nextReturn == nextInsert)
		return KEYBOARD_BUFFER_EMPTY;

	c = keyBuffer[nextReturn].value;
	lastReturn = nextReturn;
	if (c == '\n')
	{
		entersCounter--;
	}
	return c;
}


int keyboard_canRead()
{
	return entersCounter > 0 ? TRUE : FALSE;
}

void keyboard_changeKeyboard()
{
	currentKeyboard = !currentKeyboard;
	return;
}

static key_t process(unsigned char scannedCode)
{
	key_t key = {0,0};
	int pressed = 0;
	unsigned char c = scannedCode;
	int asciiCode = 0;

	// Checks if it there is an inform of extended scan code
	if (scannedCode == EXTENDED_SCAN_CODE)
	{
		// If so, prepares the context to receive the extended scan code
		waitingExtendedScanncode = TRUE;
		key.type = EXTENDED_SCAN_CODE;
		key.value = 0;
		return key;
	}

	// Checks if it is a press or a release
	pressed = (scannedCode > 0x80 ? FALSE : TRUE);
	
	if (!pressed)
	{
		c -= 0x80;
	}

	// Clasifies the type of key, while does the coresponding actions.
	if (isFunctional(c, pressed))
	{
		key.type = FUNCTIONAL;
		key.value = c;
	}
	else if (!pressed)
	{
		key.type = RELEASED;
		key.value = scannedCode;
	} 
	else if ((asciiCode = getAsciiCode(c)) != NOT_PRINTABLE)
	{
		key.type = PRINTABLE;
		key.value = asciiCode;
	}
	else
	{
		key.type = NOT_CLASIFIED_FUNCTIONAL;
		key.value = c;
	}

	// Informs that, if the function was waiting an extended scan code 
	// to process, it has been already processed
	if (waitingExtendedScanncode)
	{
		waitingExtendedScanncode = FALSE;
	}

	return key;
}

static int isFunctional(unsigned char c, int pressed)
{
	int isFunctional = TRUE;
	if (waitingExtendedScanncode)
	{
		switch(c)
		{
			case ALTGR:
				altgrPressed = pressed;
				break;
			default:
				isFunctional = FALSE;
				break;
		}
	}
	else
	{
		switch(c)
		{
			case LEFT_CONTROL:
				ctrlPressed = pressed;
				break;
			case LEFT_SHIFT:
			case RIGHT_SHIFT:
				shiftPressed = pressed;
				break;
			case LEFT_ALT:
				altPressed = pressed;
				break;
			case CAPS_LOCK:
				if (pressed) 
				{
					capsEnable = !capsEnable;
				}
				break;
			case NUM_LOCK:
				if (pressed)
				{
					keyPadEnable = !keyPadEnable;
				}
				break;
			case TAB:
				if (!pressed)
				{
					isFunctional = FALSE; // Because it is RELEASED
				}
				break;
			default:
				isFunctional = FALSE;
				break;
		}
	}
	return isFunctional;
}


static int getAsciiCode(unsigned char c)
{
	int ascii = 0, selectCase = 0;

	if (altgrPressed || waitingExtendedScanncode)
	{
		return keys[currentKeyboard][c][2];
	}
	if (isKeyPadKey(c))
	{
		return keys[currentKeyboard][c][keyPadEnable];
	}

	/*	
	 * Done this way because, if the ascii code does not correspond to an 
	 * alphabetic character, the value from the requested key
	 * will be already saved at the variable ascii, taking into consideration
	 * the shiftPressed state.
	 */
	ascii = keys[currentKeyboard][c][shiftPressed];

	// If ascii was an alphabetic character --> it gets the corresponding 
	// case of the key, based on the flags status.
	if (isAlpha(ascii))
	{
		selectCase = 	(shiftPressed || capsEnable) 
						&& !(shiftPressed && capsEnable);
		ascii = keys[currentKeyboard][c][selectCase];
	}
	return ascii;
}


static int isAlpha(unsigned char c)
{
	if (c >= 'a' && c <= 'z')
		return TRUE;
	if (c >= 'A' && c <= 'Z')
		return TRUE;
	return FALSE;
}


static int isKeyPadKey(unsigned char c)
{
	if (c >= FIRST_KEY_PAD_CODE && c <= LAST_KEY_PAD_CODE)
	{
		return TRUE;
	}
	return FALSE;
}