#include <syscalls.h>
#include <manager.h>

unsigned int manage_read(char * buffer, unsigned int length); 	// TODO: Add file descriptor?
unsigned int manage_write(char * string, unsigned int length); 	// TODO: Add file descriptor?

int syscall_read(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * buffer = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	switch(fd) {
		case _FILEDESCRIPTOR_STDIN:
			return manage_read(buffer, count); // TODO: manager_write_stdout?

		default:
			return _ERROR_SYSCALL_FILEDESCRIPTOR;
	}
}

int syscall_write(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9) {
	int fd = (int) rdi;
	char * string = (char *) rsi;
	unsigned int count = (unsigned int) rdx;

	switch(fd) {
		case _FILEDESCRIPTOR_STDOUT:
			return manage_write(string, count); // TODO: manager_write_stdout?

		default:
			return _ERROR_SYSCALL_FILEDESCRIPTOR;
	}
}
