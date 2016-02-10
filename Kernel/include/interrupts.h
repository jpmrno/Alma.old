#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

/**
 * Enables INTR hardware interrupts
 */
void interrupt_set();

/**
 * Disables INTR hardware interrupts
 */
void interrupt_clear();

#endif