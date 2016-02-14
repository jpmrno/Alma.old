#include <define.h>
#include <interrupts.h>
#include <pit.h>
#include <pic.h>
#include <log.h>

extern void _interrupt_set();
extern void _interrupt_clear();

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
