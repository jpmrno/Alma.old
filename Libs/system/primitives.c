#include <define.h>
#include <primitives.h>

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
uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9, uint64_t rax);

int sysread(char * buffer, int length) {
	return (int) _syscall(_FILEDESCRIPTOR_STDIN, (uint64_t) buffer, (uint64_t) length, NULL, NULL, NULL, _SYSCALL_READ);
}

int syswrite(char * string, int length) {
	return (int) _syscall(_FILEDESCRIPTOR_STDOUT, (uint64_t) string, (uint64_t) length, NULL, NULL, NULL, _SYSCALL_WRITE);
}

int systime(int operation, time_st * time) {
	return (int) _syscall((uint64_t) operation, (uint64_t) time, NULL, NULL, NULL, NULL, _SYSCALL_TIME);
}

int systerminal_select(int index) {
	return (int) _syscall((uint64_t) index, NULL, NULL, NULL, NULL, NULL, _SYSCALL_TERMINAL_SELECT);
}

void systerminal_clear() {
	_syscall(NULL, NULL, NULL, NULL, NULL, NULL, _SYSCALL_TERMINAL_CLEAR);
}

void systerminal_color(int operation, style_st color) {
	_syscall((uint64_t) operation, (uint64_t) color, NULL, NULL, NULL, NULL, _SYSCALL_TERMINAL_COLOR);
}

int systerminal_cursor(cursor_st cursor) {
	return (int) _syscall((uint64_t) cursor, NULL, NULL, NULL, NULL, NULL, _SYSCALL_TERMINAL_CURSOR);
}
