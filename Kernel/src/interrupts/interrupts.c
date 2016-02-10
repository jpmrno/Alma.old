#include <define.h>
#include <interrupts.h>
#include <log.h>

extern void _interrupt_set();
extern void _interrupt_clear();

void interrupt_set() {
	_interrupt_set();

#ifdef _DEGUB_ENABLED
	log("\n<STI>\n");
#endif
}

void interrupt_clear() {
	_interrupt_clear();
	
#ifdef _DEGUB_ENABLED
	log("\n<CLI>\n");
#endif
}

