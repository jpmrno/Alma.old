#ifndef _LIB_STDIO_H_
#define _LIB_STDIO_H_

#include <sysio.h>
#include <stdarg.h>

int scanc();
int scanf(char * buffer, int maxSize);
int scanw(char * buffer, int maxSize);

int printc(char character);
int prints(char * string);
int printn(int number, unsigned int base);
int printf(char * fmt, ...);
int vprintf(char * fmt, va_list arg);

#endif