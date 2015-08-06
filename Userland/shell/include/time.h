#ifndef _TIME_T_H_
#define _TIME_T_H_

#include <stdint.h>
#include "define.h"

#define TIME_INVALID -1

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
} systemTime_t;

/**
 * Reads the date and time from the RTC, and stores the data at t
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int setSystemTime(systemTime_t * t);

/**
 * Writes the data of the given t at the RTC
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int getSystemTime(systemTime_t * t);

/**
 * Analizes if the time (t) is a valid one
 * @param  t  	the time
 * @return   	TRUE if time is valid or FALSE otherwise
 */
int isValidTime(systemTime_t * t);

/**
 * Analizes if the year is leap
 * @param  year 	the year to analize
 * @return     		TRUE if year is leap or FALSE otherwise
 */
int isLeap(int year);

#endif