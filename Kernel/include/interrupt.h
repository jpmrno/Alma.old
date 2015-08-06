#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <define.h>

/**
 * Timertick interrupt. IRQ 0x00, INT 0x20
 * This IRQ runs whenever the PIT sends a signal to the processor
 */
void _timer_tick_interrupt();

/**
 * Keyboard interrupt. IRQ 0x01, INT 0x21
 * This IRQ runs whenever there is input on the keyboard
 */
void _keyboard_interrupt();

/**
 * Syscall interrupt. INT 0x80
 * This IRQ runs whenever an 'int 80h' instruction is executed. 
 */
void _syscall_interrupt();

/**
 * Applies the given mask to the PIC to enable/disable interrupts
 * @param i - the mask to be applied to the PIC    
 */
void _pic_master_mask(uint8_t i);

/**
 * Enables INTR hardware interrupts
 */
void _sti();

/**
 * Disables INTR hardware interrupts
 */
void _cli();

#endif