#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <define.h>
#include <sys_calls.h>

typedef int syscall_st(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9); // Return long?

syscall_st syscall_read;
syscall_st syscall_write;
syscall_st syscall_time;
syscall_st syscall_terminal_select;
syscall_st syscall_terminal_clear;
syscall_st syscall_terminal_color;
syscall_st syscall_terminal_cursor;

#endif
