#ifndef _SYSCALL_HANDLERS_H_
#define _SYSCALL_HANDLERS_H_

#include <define.h>
#include <syscalls.h>

/**
 * Chooses a function according to the given 'dest' number.
 * 
 * @param dest  - the number to choose the function
 * @return 		- a pointer to the chosen function, if the number has one associated; NULL otherwise
 */
uint64_t (*syscallHandler(unsigned int dest)) (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

#endif