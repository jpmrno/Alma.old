#include <syscalls.h>
#include <manager.h>

extern unsigned int manage_read(int fd, char * buffer, unsigned int length);
extern unsigned int manage_write(int fd, char * string, unsigned int length);

int syscall_read(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * buffer = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return manage_write(fd, buffer, count); // TODO: manager_write_stdout?
}

int syscall_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * string = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	return manage_write(fd, string, count); // TODO: manager_write_stdout?
}
