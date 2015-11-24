#ifndef _INT_80_H_
#define _INT_80_H_

#include <define.h>

/**
 * Syscall caller or wrapper
 * Makes the real assembly int 80h call
 * @param  rdi			
 * @param  rsi			
 * @param  rdx 		syscalls 
 * @param  r10 		parameters
 * @param  r8  			
 * @param  r9  
 * @param  rax		the syscall # to execute
 * @return     
 */
uint64_t _int80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9, uint64_t rax);

#endif