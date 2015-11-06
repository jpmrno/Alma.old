#include <syscallHandlers.h>
#include <manager.h>
#include <rtc.h>

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that reads from the given file descriptor 
 * count or less characters, and stores them at the given buffer.
 * 
 * @param  rdi - the file descriptor from where to read
 * @param  rsi - a pointer to the buffer where to save the read characters
 * @param  rdx - the amount of characters that will be read
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return     - how many characters were actually read; -1 if error
 */
static uint64_t read_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

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
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function, that writes to the given file descriptor count 
 * or less characters, taken from the given buffer.
 * 
 * @param  rdi - the file descriptor where to write
 * @param  rsi - a pointer to the buffer from where to take the characters
 * @param  rdx - the amount of characters that will be written
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return     - how many characters were actually written; -1 if error
 */
static uint64_t write_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

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

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that clears the current terminal screen.
 * 
 * @param  rdi - ignored (left for possible future implementation purposes)
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
static uint64_t terminal_clear_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that sets the terminal identified by the given identifier
 * 
 * @param  rdi - the desired terminal's identifier 
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
static uint64_t terminal_set_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);


/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that sets the given color for all the current terminal's screen
 * If text param is not equal to 0, then the color is applied to
 * the text. Else, it is applied to the background.
 * 
 * @param  rdi - whether to apply the color to the text ( != 0 ) 
 *               	or to the background ( == 0)
 * @param  rsi - the desired color to be applied
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
static uint64_t terminal_color_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that enables / disables the screen saver, 
 * depending on the value given by enabled
 * 		If enabled != 0 --> the screensaver is enabled
 *   	If enabled == 0 --> the screensaver is disabled
 * 
 * @param  rdi - whether to enable ( != 0 ) or disable ( == 0 ) 
 *                 	 the screensaver
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return     		 OK if the changed could be applied.
 *                   !OK otherwise.
 */
static uint64_t set_screen_saver_enabled_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that sets how many seconds the system will wait 
 * to display the screensaver
 * @param  rdi - the time, in seconds, to display the screensaver
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return       	 OK if the changed could be applied.
 *                   !OK otherwise.
 */
static uint64_t set_screen_saver_time_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that reads the date and time from the RTC, 
 * and stores the data at the given RTC_time structure
 * @param  rdi - the pointer to the structure where to save the date & time
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return        OK if process could be completed.
 *                !OK otherwise
 */
static uint64_t read_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * Receives all the assembly registers from the _syscall_interrupt
 * function (see: interrupt.asm) and uses the necessary ones to call 
 * the function that writes the data of the given RTC_time structure at the RTC
 * @param  rdi - the pointer to the structure from where to take the date&time
 * @param  rsi - ignored (left for possible future implementation purposes)
 * @param  rdx - ignored (left for possible future implementation purposes)
 * @param  r10 - ignored (left for possible future implementation purposes)
 * @param  r8  - ignored (left for possible future implementation purposes)
 * @param  r9  - ignored (left for possible future implementation purposes)
 * @return       OK if process could be completed
 *               !OK otherwise
 */
static uint64_t write_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

/**
 * // TODO: Documentation
 */
static uint64_t set_screen_saver_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

uint64_t (*syscallHandler(unsigned int dest)) (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	switch(dest) {
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
		case SYS_SCREENSAVER:
			return set_screen_saver_wrapper;
		default:
			break;
	}

	return NULL;
}

static uint64_t read_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * buffer = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return read(fd, buffer, count);
}

static int read(int fd, char *buffer, unsigned int count) {
	switch(fd) {
		case STDIN:
			return manager_readSTDIN(buffer, count);

		default:
			break;
	}

	return ERROR_FILEDESCRIPTOR;
}

static uint64_t write_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * str = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return write(fd, str, count);
}

static int write(int fd, char *str, unsigned int count) {
	switch(fd) {
		case STDOUT:
			return manager_writeSTDOUT(str, count);

		default:
			break;
	}

	return ERROR_FILEDESCRIPTOR;
}

static uint64_t terminal_clear_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_clearScreen();
}

static uint64_t terminal_set_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_setTerminal((unsigned int) rdi);
}


static uint64_t terminal_color_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_setColor((int) rdi, (uint8_t) rsi);
}

static uint64_t set_screen_saver_enabled_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_setScreenSaverEnabled((int) rdi);
}

static uint64_t set_screen_saver_time_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_setScreenSaverTime(rdi);
}

static uint64_t read_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
    return readRTC((RTC_time *) rdi);
}

static uint64_t write_rtc_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
    return writeRTC((RTC_time *) rdi);
}

// TODO: Remove
typedef void (* tScreenSaver) (void);


static uint64_t set_screen_saver_wrapper(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manager_setScreenSaver((int) rdi, (tScreenSaver) rsi, (int) rdx, (int) r10);
}
