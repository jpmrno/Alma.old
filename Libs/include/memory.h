#ifndef _LIB_MEMORY_H_
#define _LIB_MEMORY_H_

#include <stdint.h>

void * memset(void * destination, int32_t c, uint64_t length);

void * memcpy(void * destination, const void * source, uint64_t length);

#endif