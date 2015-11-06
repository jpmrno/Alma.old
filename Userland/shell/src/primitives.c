#include <primitives.h>
#include <int80.h>

int read(char * buffer, int length)
{
	return _int80(STDIN, (uint64_t) buffer, length, 0, 0, 0, SYS_READ);
}

int write(char * buffer, int length)
{
	return _int80(STDOUT, (uint64_t) buffer, length, 0, 0, 0, SYS_WRITE);
}

int terminal_clear()
{
	return _int80(0, 0, 0, 0, 0, 0, SYS_TERMINAL_CLEAR);
}

int terminal_set(int index)
{
	return _int80((uint64_t) index, 0, 0, 0, 0, 0, SYS_TERMINAL_SET);
}

int terminal_color(unsigned int text, unsigned char color)
{
	return _int80((uint64_t) text, (uint64_t) color, 0, 0, 0, 0, 
		SYS_TERMINAL_COLOR);
}

int time_read(systemTime_t * t)
{
	return _int80((uint64_t) t, 0, 0, 0, 0, 0, SYS_TIME_READ);
}

int time_write(systemTime_t * t)
{
	return _int80((uint64_t) t, 0, 0, 0, 0, 0 , SYS_TIME_WRITE);
}

int screensaver_enabled(unsigned int boolean)
{
	return _int80((uint64_t) boolean, 0, 0, 0, 0, 0, SYS_SCREENSAVER_ENABLE);
}

int screensaver_time(int seconds)
{
	return _int80((uint64_t) seconds, 0, 0, 0, 0, 0, SYS_SCREENSAVER_TIME);
}

int screensaver_set(int enabled, char * text, int seconds, int loop) 
{
	return _int80((uint64_t) enabled, (uint64_t) text, (uint64_t) seconds, (uint64_t) loop, 0, 0, SYS_SCREENSAVER);
}

// int screensaver_text(char * text)
// {
// 	return _int80((uint64_t) text, 0, 0, 0, 0, 0, SYS_SCREENSAVER_TEXT);
// }
