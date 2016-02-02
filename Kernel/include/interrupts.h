#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <define.h>

/**
 * Applies the given mask to the PIC to enable/disable interrupts
 * @param i - the mask to be applied to the PIC    
 */
void _interrupt_pic_mask(uint8_t i);

/**
 * Enables INTR hardware interrupts
 */
void _interrupt_set();

/**
 * Disables INTR hardware interrupts
 */
void _interrupt_clear();

#endif