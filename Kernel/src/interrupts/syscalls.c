#include <syscalls.h>
#include <manager.h>
#include <rtc.h> // TODO: Cambiar de lugar time_st
#include <sys_io.h>
#include <sys_screen.h>
#include <sys_time.h>

extern unsigned int manage_read(unsigned int fd, char * buffer, unsigned int length);
extern unsigned int manage_write(unsigned int fd, const char * string, unsigned int length);
extern int manage_rtc(int operation, time_st * time);
extern int manage_terminal(int operation, int value);

int syscall_read(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * buffer = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return manage_read(fd, buffer, count);
}

int syscall_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (unsigned int) rdi;
	char * string = (const char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return manage_write(fd, string, count);
}

int syscall_time(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int operation = (int) rdi;
	time_st * time = (time_st *) rsi;

	return manage_rtc(operation, time);
}

int syscall_terminal_select(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int index = (int) rdi;

	return manage_terminal(_TERMINAL_OPERATION_SELECT, index);
}

int syscall_terminal_clear(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	return manage_terminal(_TERMINAL_OPERATION_CLEAR, 0);
}

int syscall_terminal_color(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int operation = (int) rdi;
	int color = (int) rsi;

	return manage_terminal(operation, color);
}

int syscall_terminal_cursor(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int cursor = (int) rdi;

	return manage_terminal(_TERMINAL_OPERATION_CURSOR, cursor);
}
