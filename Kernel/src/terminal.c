#include <terminal.h>
#include <video.h>

#define TAB_SIZE 3

static char cBuffer[128] = {0};

#define MAX_SCREENS 2
#define EMPTY 1
#define FULL 0

typedef struct {
	int state;
	unsigned int cursor;
	uint8_t style;
	uint8_t content[VIDEO_ROWS * VIDEO_COLUMNS];
	uint8_t styles[VIDEO_ROWS * VIDEO_COLUMNS];
} tScreen;

static tScreen screens[MAX_SCREENS] = {
	{EMPTY}, {EMPTY}
};
static int actualScreen;
static uint16_t cursorLockedAt = 0;


/**
 * Backups the current screen at the current terminal.
 */
static void backupScreen();

/**
 * Restores to screen the terminal that matches the given index.
 * @param index 		the index of the desired terminal
 */
static void restoreScreen(unsigned int index);

/**
 * Prints the given number on the given base to the screen.
 * @param value 		the number to be printed
 */
static void printBase(uint64_t value, uint32_t base);

/**
 * Transforms the given value at the given base into its string representation.
 * @param  value  - the value to be transformed
 * @param  buffer - where to save the transformation
 * @param  base   - the base of the given value
 * @return        the amount of digits the value had (== the string's length)
 */
static unsigned int uintToBase(uint64_t value, char * buffer, uint32_t base);


static void backupScreen() {
	int i;

	screens[actualScreen].state = FULL;
	screens[actualScreen].cursor = getCursor();
	screens[actualScreen].style = getStyle();

	for (i = 0; i < VIDEO_COLUMNS * VIDEO_ROWS; i++) {
		screens[actualScreen].content[i] = get(i);
		screens[actualScreen].styles[i] = getStyleOf(i);
	}
}


static void restoreScreen(unsigned int index) {
	int i;

	screens[index].state = EMPTY;

	// Copy screen into video memory
	for(i = 0; i < (VIDEO_ROWS * VIDEO_COLUMNS); i++) {
		put(screens[index].content[i], i);
		putStyleOf(screens[index].styles[i], i);
	}

	// Reset style & cursor position
	setStyle(screens[index].style);
	setCursor(screens[index].cursor);

	// Sets screen as actual
	actualScreen = index;
}


static void printBase(uint64_t value, uint32_t base) {
    uintToBase(value, cBuffer, base);
    print(cBuffer);
}

static unsigned int uintToBase(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do {
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


int terminal_lockCurrentScreen()
{
	cursorLockedAt = getCursor();
	return OK;
}


void initTerminal() {
	int i;

	// Clears screen, sets cursor position & shape
	initVideo();

	// Saving video initial state in every screen
	// Setting default screen 0
	for(i = (MAX_SCREENS - 1); i >= 0; i--) {
		actualScreen = i;
		backupScreen();
	}
}


void clearScreen() {
	// Clears screen & resets cursor position
	clearAll();
}


int setScreen(unsigned int index) {
	// If screen index is out of bounds return ERROR
	if(index >= MAX_SCREENS) {
		return ERROR_SCREEN_INVALID;
	}

	// If you want to set the screen that is already set, returns OK
	if(actualScreen == index) {
		return OK;
	}

	// Backup actual screen
	backupScreen();

	// Selects the screen wanted as actual
	// Copy from backup space to video memory 
	restoreScreen(index);

	return OK;
}


void screenSaver_start() {
	// Backup actual screen
	backupScreen();

	// Clear screen for screen saver to write
	clearScreen();
}


void screenSaver_stop() {
	// Copys into video memory the last used screen
	restoreScreen(actualScreen);
}

	
int print(const char * string) {
	int i = 0;

	while(string[i]) {
		printChar(string[i++]);
	}

	return i;
}


void println() {
	newLine();
}


void printChar(char character) {
	int tab = TAB_SIZE;

	switch(character) {
		case '\n': // New line
			newLine();
			break;

		case '\t': // Tab
			while(tab--) {
				write(' ');
			}
			break;

		case '\b': // Backspace
			if (getCursor() > cursorLockedAt)
			{
				delete();
			}
			break;

		default: // Normal Character
			write(character);
			break;
	}
}


void printInt(uint64_t value) {
	printBase(value, 10);
}


void printHex(uint64_t value) {
	printBase(value, 16);
}


void printBin(uint64_t value) {
	printBase(value, 2);
}

void setTerminalColor(uint8_t color) {
	colorAll(color);
}

void setTerminalBackground(uint8_t color) {
	backgroundAll(color << 4);
}
