#ifndef _CMOS_H_
#define _CMOS_H_

/**
 * Writes the given value at the desired CMOS address  
 * @param port  - the address to be written
 * @param value - the value to be written
 */
void _write_CMOS(int port, int value);

/**
 * Reads from the CMOS address
 * @param  port - the address to be read  
 * @return      - the read value	
 */
int _read_CMOS(int port);

#endif