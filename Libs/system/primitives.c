#include <primitives.h>
#include <int80.h>

int read(char * buffer, int length) {
	return _int80(STDIN, (uint64_t) buffer, length, NULL, NULL, NULL, SYSTEM_CALL_READ);
}

int write(char * buffer, int length) {
	return _int80(STDOUT, (uint64_t) buffer, length, NULL, NULL, NULL, SYSTEM_CALL_WRITE);
}

int terminal_clear() {
	return _int80(NULL, NULL, NULL, NULL, NULL, NULL, SYSTEM_CALL_TERMINAL_CLEAR);
}

int terminal_set(int index) {
	return _int80((uint64_t) index, NULL, NULL, NULL, NULL, NULL, SYSTEM_CALL_TERMINAL_SET);
}

int terminal_color(unsigned int text, unsigned char color) {
	return _int80((uint64_t) text, (uint64_t) color, NULL, NULL, NULL, NULL, SYSTEM_CALL_TERMINAL_COLOR);
}

int time_read(tSystemTime * t) {
	return _int80((uint64_t) t, NULL, NULL, NULL, NULL, NULL, SYSTEM_CALL_TIME_READ);
}

int time_write(tSystemTime * t) {
	return _int80((uint64_t) t, NULL, NULL, NULL, NULL, NULL , SYSTEM_CALL_TIME_WRITE);
}

int screensaver_set(int enabled, char * text, int seconds, int loop)  {
	return _int80((uint64_t) enabled, (uint64_t) text, (uint64_t) seconds, (uint64_t) loop, NULL, NULL, SYSTEM_CALL_SCREENSAVER);
}

int screensaver_enabled(unsigned int boolean) {
	return _int80((uint64_t) boolean, NULL, NULL, NULL, NULL, NULL, SYSTEM_CALL_SCREENSAVER_ENABLE);
}

int screensaver_time(int seconds) {
	return _int80((uint64_t) seconds, NULL, NULL, NULL, NULL, NULL, SYSTEM_CALL_SCREENSAVER_TIME);
}
