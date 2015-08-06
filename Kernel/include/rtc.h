#ifndef _RTC_H_
#define _RTC_H_ 

#include <define.h>

#define SECONDS	0x00
#define MINUTES 0x02
#define HOURS 0x04
#define DAY 0x07
#define MONTH 0x08
#define YEAR 0x09
#define CENTURY 0x32

#define STATUS_REGISTER_A 0x0A
// Bit 7 of STATUS_REGISTER_A enabled
#define UPDATE_IN_PROGRESS_MASK 0x80

#define STATUS_REGISTER_B 0x0B
//Bit 2 of STATUS_REGISTER_B enabled
#define BINARY_MODE_MASK 0x04
//Bit 1 of STATUS_REGISTER_B enabled
#define HOUR_24_MODE_MASK 0x02

//Bit 7 of hour register enabled
#define HOUR_PM 0x80

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint16_t year;
} RTC_time;


/**
 * Reads the date and time from the RTC, and stores the data
 * at the given RTC_time structure
 * @param  t                  the RTC_time structure
 * @return                    OK if process could be completed
 *                  		  !OK otherwise
 */
uint64_t readRTC(RTC_time* t);


/**
 * Writes the data of the given RTC_time structure at the RTC
 * @param  t                  the RTC_time structure
 * @return                    OK if process could be completed
 *                            !OK otherwise
 */
uint64_t writeRTC(RTC_time* t);

#endif