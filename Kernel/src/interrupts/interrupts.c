#include <interrupts.h>
#include <define.h>
#include <pit.h>
#include <pic.h>
#include <syscalls.h>
#include <log.h>
#include <output.h>

extern void _interrupt_set();
extern void _interrupt_clear();

void interrupt_20();
void interrupt_21(unsigned char scancode);
syscall_st * interrupt_80(int syscall);

void interrupt_set() {
	_interrupt_set();

	#ifdef _DEGUB_ENABLED
	log("<STI>\n");
	#endif
}

void interrupt_clear() {
	_interrupt_clear();
	
	#ifdef _DEGUB_ENABLED
	log("<CLI>\n");
	#endif
}

void interrupt_20() {
	pit_trigger();
	pic_irq_eoi(0);
}

void interrupt_21(unsigned char scancode) {
	keyboard_trigger(scancode);
	pic_irq_eoi(1);
}

syscall_st * interrupt_80(int syscall) {
	switch(syscall) {
		case _SYSCALL_READ:
			return syscall_read;
		case _SYSCALL_WRITE:
			return syscall_write;
		case _SYSCALL_TIME:
			return syscall_time;
		case _SYSCALL_TERMINAL_SELECT:
			return syscall_terminal_select;
		case _SYSCALL_TERMINAL_CLEAR:
			return syscall_terminal_clear;
		case _SYSCALL_TERMINAL_COLOR:
			return syscall_terminal_color;
		case _SYSCALL_TERMINAL_CURSOR:
			return syscall_terminal_cursor;
		default:
			break;
	}

	return NULL;
}
