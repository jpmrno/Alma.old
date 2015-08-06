#include <time.h>
#include <primitives.h>

int setSystemTime(systemTime_t * t) {
	return isValidTime(t) ? time_write(t) : TIME_INVALID;
}

int getSystemTime(systemTime_t * t) {
	return time_read(t);
}

int isValidTime(systemTime_t * t) {
	static int days[][13]= {
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
	};
	int leap, maxDays;

	if (  t->second >= 60 || t->minute >= 60 || t-> hour >= 24)
		return FALSE;

    if (t->day >=32 || t->day == 0|| t->month >= 13 || t->month == 0)
        return FALSE;

    if (t->year < 1980 || t->year > 2250)
    	return FALSE;

    leap = isLeap(t->year);
    maxDays = days[leap][t->month];
      
	if (t->day > maxDays)
		return FALSE;
     
	return TRUE;
}

int isLeap(int year) {
	if (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0))
		return TRUE;
	return FALSE;
}
