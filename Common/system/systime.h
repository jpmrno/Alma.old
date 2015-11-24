#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

// TODO: Errors

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
} tSystemTime;

// TODO: Sync systime.h with kernel and time.h

#endif