#include <manager.h>
#include <keyboard.h>
#include <terminal.h>
#include <syscalls.h>

typedef void (* tScreenSaver) (void);

#define CONVERT_TO_TIMER_TICK_CYCLES(x) (((x) * 1000) / 55)

static int keyboardPrintToScreen_enabled = FALSE;
static int keyboardPrintToScreen_backup = FALSE;
static int terminalWriteInUsage = FALSE;

static uint64_t screenSaver_counterLimit = CONVERT_TO_TIMER_TICK_CYCLES(30);
static uint64_t screenSaver_counter = 0;
static int screenSaver_active = FALSE;
static int screenSaver_enabled = FALSE;
static int screenSaver_loop = FALSE;
static char * screenSaver_text;

/**
 * Recieves a key pointer and decides what action to perform, 
 * depending on the manager's flag status and the kind of key it is.
 *
 * IMPORTANT: This function should be only used by the keybardHandler function
 * at: keyboard.c. That's why its declaration is not included at: manager.h
 * @param key - the key to decide which action to perform
 */
void manager_keyReceived(key_t *key) {
	if (key->type == PRINTABLE) {
		if (key->value == '\b') {
			// If the key cannot be erased, nothing is done for now.
			keyboard_eraseLastCharacter();
		} else {
			if (!screenSaver_active) {
				// If the key cannot be buffered, nothing is done for now.
				keyboard_buffer(key);
			}
		}

		if (keyboardPrintToScreen_enabled) {
			printChar(key->value);
		}
	}

	if(screenSaver_active) {
		screenSaver_active = FALSE;
		screenSaver_stop();
		keyboardPrintToScreen_enabled = keyboardPrintToScreen_backup;
	} else {
		if (key->type == FUNCTIONAL && key->value == TAB) {
			keyboard_changeKeyboard();
		}
	}
	screenSaver_counter = 0;
}

/**
 * Receives a signal from the timerTickHandler function (see: timertick.c)
 * each time that function is called.
 *
 * IMPORTANT: This function should be only used by the timerTickHandler
 * function at: timertick.c. That's why its declaration is not included 
 * at: manager.h
 */
void manager_timerTickInterrupt() {
	if (!screenSaver_enabled) {
		return;
	}

	if(!screenSaver_active) {
		if(screenSaver_counter < screenSaver_counterLimit) {
			screenSaver_counter++;
		} else if(!terminalWriteInUsage) {
			screenSaver_counter = 0;
			screenSaver_active = TRUE;
			keyboardPrintToScreen_backup = keyboardPrintToScreen_enabled;
			keyboardPrintToScreen_enabled = FALSE;
			screenSaver_start();
			print(screenSaver_text);
		}
	} else {
		if(screenSaver_loop) {
			print(screenSaver_text);
		}
	}
}

int manager_readSTDIN(char *buffer, unsigned int count) {
	int i = 0;

	keyboardPrintToScreen_enabled = TRUE;
	terminal_lockCurrentScreen();

	while (!keyboard_canRead());

	while (i<count && keyboard_canRead()) {
		buffer[i++] = keyboard_getChar();
	}

	terminal_lockCurrentScreen();
	keyboardPrintToScreen_enabled = FALSE;

	return i;
}

int manager_writeSTDOUT(const char * string, unsigned int length) {
	int i = 0;

	terminalWriteInUsage = TRUE;

	while(i < length && string[i]) {
		terminal_lockCurrentScreen(); // So as anyone can delete what has been written
		printChar(string[i++]);
	}
	terminal_lockCurrentScreen(); // Same as above

	terminalWriteInUsage = FALSE;
	screenSaver_counter = 0;

	return i;
}

int manager_clearScreen() {
	clearScreen();
	return OK;
}

int manager_setTerminal(unsigned int index) {
	return setScreen(index - 1);
}

int manager_setColor(int text, uint8_t color) {
	if(text) {
		setTerminalColor(color);
	} else {
		setTerminalBackground(color);
	}

	return OK;
}

int manager_setScreenSaverEnabled(int enabled) {
	screenSaver_enabled = enabled ? TRUE : FALSE;
	screenSaver_counter = 0;
	return OK;
}

int manager_setScreenSaverTime(uint16_t seconds) {
	screenSaver_counterLimit = CONVERT_TO_TIMER_TICK_CYCLES(seconds);
	return OK;
}

int manager_setScreenSaver(int enabled, char * text, int seconds, int loop) {
	if(enabled) {
		if(seconds < SCREENSAVER_TIME_MIN) {
			return ERROR_SCREENSAVER_TIME;
		}
		screenSaver_text = text;
		screenSaver_counterLimit = CONVERT_TO_TIMER_TICK_CYCLES(seconds);
		screenSaver_loop = loop ? TRUE : FALSE;
	}
	screenSaver_enabled = enabled ? TRUE : FALSE;
	screenSaver_counter = 0; // TODO: Porque??

	return OK;
}
