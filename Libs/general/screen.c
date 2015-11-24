#include <screen.h>
#include <primitives.h>

#define SYSTEM_TERMINAL_COLOR_TEXT 1
#define SYSTEM_TERMINAL_COLOR_BG 0

void clearScreen() {
	terminal_clear();
}

int setTerminal(int index) {
	if(index < 0 || index > SYSTEM_TERMINAL_MAX) {
		return SYSTEM_ERROR_TERMINAL_INVALID;
	}

	return terminal_set(index);
}

int setTerminalTextColor(unsigned char color) {
	if(color < SYSTEM_TERMINAL_COLOR_MIN || color > SYSTEM_TERMINAL_COLOR_MAX) {
		return SYSTEM_ERROR_TERMINAL_COLOR_INVALID;
	}

	terminal_color(SYSTEM_TERMINAL_COLOR_TEXT, color);
	return OK;
}

int setTerminalBackgroundColor(unsigned char color) {
	if(color < SYSTEM_TERMINAL_COLOR_MIN || color > SYSTEM_TERMINAL_COLOR_MAX) {
		return SYSTEM_ERROR_TERMINAL_COLOR_INVALID;
	}

	terminal_color(SYSTEM_TERMINAL_COLOR_BG, color);
	return OK;
}

int setScreenSaverTime(int seconds) {
	if(seconds < SYSTEM_SCREENSAVER_TIME_MIN) {
		return SYSTEM_ERROR_SCREENSAVER_TIME;
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

int settScreenSaver(int enabled, char * text, int seconds, int loop) {
	return screensaver_set(enabled, text, seconds, loop);
}
