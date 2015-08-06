#ifndef _TIMER_TICK_HANDLER_H_
#define _TIMER_TICK_HANDLER_H_

/**
 * Timertick interrupt Handler. IRQ 0x00, INT 0x20
 * This function should be called when the PIT sends a signal to the processor
 */
void timerTickHandler();

#endif