#ifndef _SYS_CALLS_H_
#define _SYS_CALLS_H_

// TODO: Necesarios?
#include <systime.h>
#include <sysio.h>
#include <sysscreen.h>

enum syscalls_call {
	SYS_READ = 0,
	SYS_WRITE = 1,
	SYS_TERMINAL_CLEAR = 2,
	SYS_TERMINAL_SET = 3,
	SYS_TERMINAL_COLOR = 4,
	SYS_TIME_READ = 5,
	SYS_TIME_WRITE = 6,
	SYS_SCREENSAVER_ENABLE = 7,
	SYS_SCREENSAVER_TIME = 8,
	SYS_SCREENSAVER = 9
};

#endif