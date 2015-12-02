#ifndef _LIB_ASM_H_
#define _LIB_ASM_H_

#include <define.h>

/**
 * Gets the cpu vendor
 * @param  result  - where to write the cpu vendor
 * @return         - a pointer to the string result
 */
char * cpuVendor(char * result);

/**
 * TODO: Doc
 */
void _port_write_byte(uint8_t port, uint8_t data);

#endif