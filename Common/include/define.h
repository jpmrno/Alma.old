#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>

#define NULL ((void *) 0)

#define TRUE  1
#define FALSE !TRUE

enum generalErrors {
	NO_ERROR = 0, ERROR
};

#define OK NO_ERROR

enum fileDescriptors {
	STDIN = 0, STDOUT = 1, STDERR = 2
};

#endif