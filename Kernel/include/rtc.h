#ifndef _RTC_H_
#define _RTC_H_ 

#include <define.h>

#define _RTC_TIME_INVALID -1

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
} time_st;


/**
 * Reads the date and time from the RTC, and stores the data
 * at the given time_st structure
 * @param  t                  the time_st structure
 * @return                    OK if process could be completed
 *                  		  !OK otherwise
 */
int rtc_read(time_st* t);


/**
 * Writes the data of the given time_st structure at the RTC
 * @param  t                  the time_st structure
 * @return                    OK if process could be completed
 *                            !OK otherwise
 */
int rtc_write(time_st* t);

#endif