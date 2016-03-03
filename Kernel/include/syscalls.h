#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <define.h>

enum syscall_triggers { // TODO: Move
	_SYSCALL_READ = 0,
	_SYSCALL_WRITE
};

enum file_descriptors { // TODO: Move
	_FILEDESCRIPTOR_STDOUT = 0,
	_FILEDESCRIPTOR_STDIN
};


#define _FILEDESCRIPTOR_SDOUT 0 // TODO: Move
#define _ERROR_SYSCALL_FILEDESCRIPTOR -1 // TODO: Move

typedef int syscall_st(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

syscall_st syscall_read;
syscall_st syscall_write;

#endif
