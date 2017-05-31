#include <mtos.h>

#define SECONDS_PER_YEAR	31622400

const UINT16 __MonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const UINT16 __MonthDaysL[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const UINT16 __DaysInMonth[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }; //, 365 },
const UINT16 __DaysInMonthL[12] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }; //, 366 },}


BOOL	IsLeapYear(UINT16 year) {
	return ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) ? TRUE : FALSE;
}

UINT16	MonthsToDays(UINT16 month) {
	return __DaysInMonthL[month];
}

DATETIME_S	DateToSeconds(UINT16 year, UINT8 month, UINT8 day) {
	return (year * SECONDS_PER_YEAR) + ((MonthsToDays(month) + day) * 86400);
}
