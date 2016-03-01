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

syscall_st * interrupt_80(int syscall) {
	switch(syscall) {
		case _SYSCALL_READ:
			return syscall_read;
		case _SYSCALL_WRITE:
			return syscall_write;
		default:
			break;
	}

	return NULL;
}
