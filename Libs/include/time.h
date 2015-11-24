#ifndef _LIB_TIME_H_
#define _LIB_TIME_H_

#include <define.h>
#include <sys_time.h>

#define TIME_INVALID -1 // TODO: Sync systime.h with kernel and time.h

/**
 * Reads the date and time from the RTC, and stores the data at t
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int setSystemTime(tSystemTime * t);

/**
 * Writes the data of the given t at the RTC
 * @param  t 	time
 * @return   	OK if process could be completed
 *              !OK otherwise
 */
int getSystemTime(tSystemTime * t);

/**
 * Analizes if the time (t) is a valid one
 * @param  t  	the time
 * @return   	TRUE if time is valid or FALSE otherwise
 */
int isValidTime(tSystemTime * t);

/**
 * Analizes if the year is leap
 * @param  year 	the year to analize
 * @return     		TRUE if year is leap or FALSE otherwise
 */
int isLeap(int year);

#endif