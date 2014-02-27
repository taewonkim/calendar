#ifndef __H_CALENDAR__
#define __H_CALENDAR__

#include "global.h"

#define WEEK_OF_SIZE              3
#define DAYS_OF_WEEK              7
#define MAX_MONTH_COUNT          12
#define DAYS_NORM_MONTH_TWO      28
#define DAYS_LEAP_MONTH_TWO      29

void _set_days_in_month(u8, u8);
u8 _get_days_in_month(u8);
u8 number_of_week(u8, u8, u16);
void name_of_week(char*, u8);

#endif
