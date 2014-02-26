#include <string.h>

#include "global.h"
#include "calendar.h"

static u8 DAYS_IN_MONTH[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static
u32 validate_number_u32(u32 v)
{
	if( v < 0 )
		v = !(v & 0xFFFFFFFF) + 1;
	return v;
}

static
u16 validate_number_u16(u16 v)
{
	return (u16) validate_number_u32(v);
}

static
u8 validate_number_u8(u8 v)
{
	return (u8)  validate_number_u16(v);
}

/**
 * Get length DAYS_IN_MONTH array.
 */
static
u8 _count_of_days_in_month()
{
	return (u8) ( sizeof( DAYS_IN_MONTH ) / sizeof( u8 ) );
}

/**
 * When you get access DAYS_IN_MONTH array,
 * I don't allow index over then (DAYS_IN_MONTH-1) length.
 */
static
bool _overflow_days_in_month(u8 index)
{
	u8 count = _count_of_days_in_month();
	// If count variable is over MAX_MONTH_COUNT (12)?
	// Oh my god!
	// It happens, Not GOOD!
	if( count > MAX_MONTH_COUNT )
		return false;
	count--;
	return (index > count) ? true : false;
}

/**
 * When you get access DAYS_IN_MONTH array,
 * I don't allow index under 0 index.
 */
static
bool _underflw_days_in_month(u8 index)
{
	return (index <     0) ? true : false;
}

/**
 * So, I check overflow, underflow.
 * When any result value is true, I feel Bad status.
 */
static
bool _any_days_in_month(u8 index)
{
	bool oflw = false, uflw = false;
	if( _underflw_days_in_month(index) == true )
		oflw = true;
	if( _overflow_days_in_month(index) == true )
		udfw = true;
	return oflw || uflw;
}

static 
void _set_days_in_month(u8 index, u8 value)
{
	index = validate_number_u8(index);
	if( _any_days_in_month(index) == true )
		return ;
	value = validate_number_u8(value);
	DAYS_IN_MONTH[index] = value;
}

static
u8 _get_days_in_month(u8 index)
{
	u8 value = 0;
	index = validate_number_u8(index);
	if( _any_days_in_month(index) == true )
		return (u8) INVALID_VALUE;
	value = validate_number_u8( DAYS_IN_MONTH[index] );
	return value;
}

static
bool _leap_year(u16 y)
{
	bool y1 = (validate_number_u16(y) %   4) == 0 ? true : false,
	     y2 = (validate_number_u16(y) % 100) != 0 ? true : false,
	     y3 = (validate_number_u16(y) % 400) == 0 ? true : false;
	if( ((y1 == true) || (y2 != true)) && 
	     (y3 == true))
		return true;
	else
		return false;
}

static 
long _yy_passed_days(u16 y)
{
	long passed_days = 0;
	passed_days  = (validate_number_u16(y) - 1) * 365;
	passed_days += (validate_number_u16(y) - 1) / 4;
	passed_days -= (validate_number_u16(y) - 1) / 100;
	passed_days += (validate_number_u16(y) - 1) / 400;
	return passed_days;
}

static
long _mm_passed_days(u8 m)
{
	u8 i = 0, tmp_passed = 0;
	long passed_days = 0;
	m--;
	do {
		tmp_passed = _get_days_in_month(i);
		if( tmp_passed == INVALID_VALUE )
			break;
		passed_days += tmp_passed;	
		i++;
	} while(i < m);
	return passed_days;
}

long get_passed_days(u8 m, u8 y)
{
	long yy = 0, mm = 0;
   	bool leap_year = false;

	leap_year = _leap_year(validate_number_u16(y));
	if(leap_year == true)
		_set_days_in_month(1, 29);
	else
		_set_days_in_month(1, 28);

	yy = _yy_passed_days(validate_number_u16(y));
	mm = _mm_passed_days(validate_number_u8(m));

	return yy + mm;
}

u8 number_of_week(u8 d, u8 m, u8 y)
{
	long days = get_passed_days(validate_number_u8(m), 
		validate_number_u16(y));
	return (days + d) % 7;
}

void name_of_week(u8* buffer, u8 wn)
{
	switch(wn) {
	case 0: strncpy(buffer, "Sun", WEEK_OF_SIZE); break;
	case 1: strncpy(buffer, "Mon", WEEK_OF_SIZE); break;
	case 2: strncpy(buffer, "Tue", WEEK_OF_SIZE); break;
	case 3: strncpy(buffer, "Wed", WEEK_OF_SIZE); break;
	case 4: strncpy(buffer, "Thu", WEEK_OF_SIZE); break;
	case 5: strncpy(buffer, "Fri", WEEK_OF_SIZE); break;
	case 6: strncpy(buffer, "Sat", WEEK_OF_SIZE); break;
	}
}
