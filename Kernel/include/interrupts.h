#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <define.h>

/**
 * Enables INTR hardware interrupts
 */
void _interrupt_set();

/**
 * Disables INTR hardware interrupts
 */
void _interrupt_clear();

#endif