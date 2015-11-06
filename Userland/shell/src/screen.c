#include <screen.h>
#include <primitives.h>

#define BACKGROUND 0
#define TEXT 1

void clearScreen() {
	terminal_clear();
}

int setTerminal(int index) {
	if(index < MIN_TERMINAL || index > MAX_TERMINAL) {
		return ERROR_INVALID_TERMINAL;
	}

	return terminal_set(index);
}

int setTerminalTextColor(unsigned char color) {
	if(color < MIN_COLOR || color > MAX_COLOR) {
		return ERROR_INVALID_COLOR;
	}

	terminal_color(TEXT, color);
	return OK;
}

int setTerminalBackgroundColor(unsigned char color) {
	if(color < MIN_COLOR || color > MAX_COLOR) {
		return ERROR_INVALID_COLOR;
	}

	terminal_color(BACKGROUND, color);
	return OK;
}

int setScreenSaverTime(int seconds) {
	if(seconds < MIN_SCREENSAVER_TIME) {
		return ERROR_SCREENSAVER_TIME;
	}

	screensaver_time(seconds);
	return OK;
}

void enableScreenSaver() {
	screensaver_enabled(TRUE);
}

void disableScreenSaver() {
	screensaver_enabled(FALSE);
}

int settScreenSaver(int enabled, void (* action)(void), int seconds, int loop) {
	return screensaver_set(enabled, action, seconds, loop);
}

// int setScreenSaverText(char * string) { // For future implementation
// 	return screensaver_text(string);
// }
