#ifndef _PORTS_H_
#define _PORTS_H_

#include <define.h>

#define _PORT_COM1 0x3F8 // COM1

/**
 * TODO: Doc
 */
void _port_write_byte(uint16_t port, uint8_t data);

uint8_t _port_read_byte(uint16_t port);

#endif