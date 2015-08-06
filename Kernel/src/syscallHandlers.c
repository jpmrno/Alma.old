#include <syscallHandlers.h>
#include <manager.h>
#include <rtc.h>

/**
 * Reads from the given file descriptor count or less characters,
 * and stores them at the given buffer.
 * 
 * @param  fd     - the file descriptor
 * @param  buffer - where to save the read characters
 * @param  count  - the amount of characters that will be read
 * @return        how many characters were actually read; -1 if error
 */
static int read(int fd, char *buffer, unsigned int count);

/**
 * Writes to the given file descriptor count or less characters,
 * taken from the given buffer.
 * 
 * @param  fd     - the file descriptor
 * @param  buffer - from where to take the characters
 * @param  count  - the amount of characters that will be written
 * @return        how many characters were actually written; -1 if error
 */
static int write(int fd, char *buffer, unsigned int count);

static int read(int fd, char *buffer, unsigned int count) {
	switch(fd) {
		case STDIN:
			return manager_readSTDIN(buffer, count);
		default:
			break;
	}
	return -1;
}

static int write(int fd, char *str, unsigned int count) {
	switch(fd) {
		case STDOUT:
			return manager_writeSTDOUT(str, count);
		default:
			break;
	}
	return -1;
}



uint64_t (*syscallHandler(unsigned int dest)) (uint64_t rdi,
			uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9)
{
	switch(dest) 
	{
		case SYS_READ:
			return read_wrapper;
		case SYS_WRITE:
			return write_wrapper;
		case SYS_TERMINAL_CLEAR:
			return terminal_clear_wrapper;
		case SYS_TERMINAL_SET:
			return terminal_set_wrapper;
		case SYS_TERMINAL_COLOR:
			return terminal_color_wrapper;
		case SYS_TIME_READ: 
			return read_rtc_wrapper;
		case SYS_TIME_WRITE:
			return write_rtc_wrapper;
		case SYS_SCREENSAVER_ENABLE:
			return set_screen_saver_enabled_wrapper;
		case SYS_SCREENSAVER_TIME:
			return set_screen_saver_time_wrapper;
		default:
			break;
	}

	return NULL;
}

uint64_t read_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
										uint64_t r10, uint64_t r8, uint64_t r9)
{
	int fd = (int) rdi;
	char * buffer = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return read(fd, buffer, count);
}

uint64_t write_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
										uint64_t r10, uint64_t r8, uint64_t r9)
{
	int fd = (int) rdi;
	char * str = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return write(fd, str, count);
}

uint64_t terminal_clear_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
									uint64_t r10, uint64_t r8, uint64_t r9) 
{
	return manager_clearScreen();
}

uint64_t terminal_set_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
									uint64_t r10, uint64_t r8, uint64_t r9) 
{
	return manager_setTerminal((unsigned int) rdi);
}


uint64_t terminal_color_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx,
									uint64_t r10, uint64_t r8, uint64_t r9) 
{
	return manager_setColor((int) rdi, (uint8_t) rsi);
}

uint64_t set_screen_saver_enabled_wrapper(uint64_t rdi, uint64_t rsi, 
						uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9)
{
	return manager_setScreenSaverEnabled((int) rdi);
}

uint64_t set_screen_saver_time_wrapper(uint64_t rdi, uint64_t rsi, 
						uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9)
{
	return manager_setScreenSaverTime(rdi);
}

uint64_t read_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
										uint64_t r10, uint64_t r8, uint64_t r9)
{
    return readRTC((RTC_time*) rdi);
}

uint64_t write_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, 
										uint64_t r10, uint64_t r8, uint64_t r9)
{
    return writeRTC((RTC_time*) rdi);
}
