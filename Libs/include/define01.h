#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>
#include <debug.h> // TODO: Si o no?

#define NULL ((void *) 0)

#define TRUE 1
#define FALSE !TRUE

#define OK 0
#define ERROR -1

#define ERROR_OCCURRED(x) ((x) < OK)

#endif