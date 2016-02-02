#ifndef _PIC_H_
#define _PIC_H_

#include <define.h>

// TODO: 
#define _PIC_MASK_TIMER     0
#define _PIC_MASK_KEYBOARD  1
#define _PIC_MASK_CASCADE   2
#define _PIC_MASK_COM2_4    3
#define _PIC_MASK_COM1_3    4
#define _PIC_MASK_LPT       5
#define _PIC_MASK_FLOPPY    6
#define _PIC_MASK_FREE7     7
#define _PIC_MASK_CLOCK     8
#define _PIC_MASK_FREE9     9
#define _PIC_MASK_FREE10    10
#define _PIC_MASK_FREE11    11
#define _PIC_MASK_PS2MOUSE  12
#define _PIC_MASK_COPROC    13
#define _PIC_MASK_IDE_1     14
#define _PIC_MASK_IDE_2     15
#define _PIC_MASK_ALL       0xFF

/**
 * Applies the given mask to the PIC to enable/disable interrupts
 * @param i - the mask to be applied to the PIC    
 */
void _pic_mask(uint8_t i);

#endif
