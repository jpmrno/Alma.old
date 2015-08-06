#ifndef _IDT_MANAGER_H_
#define _IDT_MANAGER_H_

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

/* Modified from: Arquitectura de las Computadoras - TP6 */
#define ACS_PRESENT     0x80            /* present segment at memory */
#define ACS_CSEG        0x18            /* code segment */
#define ACS_DSEG        0x10            /* data segment */
#define ACS_READ        0x02            /* read segment */
#define ACS_WRITE       0x02            /* write segment */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_IA_32e 	0x0E			/* Interrupt GATE 64 bits */
#define ACS_INT         ( ACS_PRESENT | ACS_INT_IA_32e ) /* DPL == 0x00 */

#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)


#define GDT_CODE_SEGMENT 0x08

/**
 * Sets a new IDT entry at the given index, with the corresponding pointer to
 * the interrupt service routine and with the detailed access permissions.  
 * @param index  -  the index of the new IDT entry, relative to 
 *               	the beginning of the IDT
 * @param offset - the pointer to the interrupt service routine
 * @param access - the permissions for the entry being set
 */
void setup_IDT_entry (int index, qword offset, byte access);

#endif