#ifndef _IDT_H_
#define _IDT_H_

#include <define.h>

/**
 * Sets a new IDT entry at the given index, with the corresponding pointer to
 * the interrupt service routine and with the detailed access permissions.  
 * @param index  -  the index of the new IDT entry, relative to 
 *               	the beginning of the IDT
 * @param offset - the pointer to the interrupt service routine
 * @param access - the permissions for the entry being set
 */
void idt_entry(int index, qword offset, byte access);

#endif