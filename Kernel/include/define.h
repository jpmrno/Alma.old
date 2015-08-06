#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdint.h>

#ifndef NULL
#define NULL (void*) 0
#endif

#define TRUE  1
#define FALSE !TRUE

enum errors {
	NO_ERROR = 0, COULD_NOT_PERFORM_OPERATION, INVALID_TIME, INVALID_KEY
};

#define OK NO_ERROR

enum fileDescriptors {
	STDIN = 0, STDOUT = 1, STDERR = 2
};

#endif