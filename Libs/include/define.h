#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>

#define NULL ((void *) 0)

#define TRUE 1
#define FALSE !TRUE

#define OK 0
#define ERROR -1

#define ERROR_OCCURRED(x) ((x) < OK)

typedef uint8_t byte_t;
typedef uint16_t word_t;
typedef uint32_t dword_t;
typedef uint64_t qword_t;

#endif