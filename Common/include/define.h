#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>

#define NULL ((void *) 0)

#define TRUE 1
#define FALSE !TRUE

#define NO_ERROR 0 // TODO: Remove
#define OK NO_ERROR
#define ERROR 1 // TODO: O -1? O !OK? ..?

// TODO: Useful??
#define ERROR_OCCURRED(x) ((x) < OK)

#endif