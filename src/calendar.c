#include <string.h>

#include "global.h"
#include "calendar.h"

static 
u8 DAYS_IN_MONTH[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

u32 shift_bits(u32 uv, shift udir)
{
	u32 rv = 0x80000000 >> udir,
	    tv = 0xFFFFFFFF >> udir;
	if( (uv & rv) == rv)
		uv = (u16) (tv - (uv & tv) + 1);
	return uv;
}

#if 0
static
u32 validate_number_u32(u32 uv)
{
	/*
	if( (uv & 0x80000000) == 0x80000000 )
		uv = (u32) (0xFFFFFFFF - (uv & 0xFFFFFFFF) + 1);
	return uv;
	*/
	return (u32) shift_bits(uv, none);
}
#endif

static
u16 validate_number_u16(u16 uv)
{
	/*
	if( (uv & 0x00008000) == 0x00008000 )
		uv = (u16) (0x0000FFFF - (uv & 0x0000FFFF) + 1);
	return uv;
	*/
	return (u16) shift_bits(uv, word);
}

static
u8 validate_number_u8(u8 uv)
{
	/*
	if( (uv & 0x00000080) == 0x00000080 )
		uv = (u8)  (0x000000FF - (uv & 0x000000FF) + 1);
	return uv;
	*/
	return (u8) shift_bits(uv, dword);
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
bool _overflow_days_in_month(u8 iv)
{
	u8 count = _count_of_days_in_month();
	// If count variable is over MAX_MONTH_COUNT (12)?
	// Oh my god!
	// It happens, Not GOOD!
	if( count > MAX_MONTH_COUNT )
		return false;
	count--;
	iv = validate_number_u8(iv);
	return (iv > count) ? true : false;
}

/**
 * When you get access DAYS_IN_MONTH array,
 * I don't allow index under 0 index.
 */
static
bool _underflw_days_in_month(u8 iv)
{
	iv = validate_number_u8(iv);
	return (iv < 0) ? true : false;
}

/**
 * So, I check overflow, underflow.
 * When any result value is true, I feel Bad status.
 */
static
bool _any_days_in_month(u8 iv)
{
	bool oflw = false, uflw = false;
	iv = validate_number_u8(iv);
	if( _underflw_days_in_month(iv) == true )
		oflw = true;
	if( _overflow_days_in_month(iv) == true )
		uflw = true;
	return oflw || uflw;
}

void _set_days_in_month(u8 iv, u8 uv)
{
	iv = validate_number_u8(iv);
	if( _any_days_in_month(iv) == true )
		return ;
	uv = validate_number_u8(uv);
	DAYS_IN_MONTH[iv] = uv;
}

u8 _get_days_in_month(u8 iv)
{
	iv = validate_number_u8(iv);
	if( _any_days_in_month(iv) == true )
		return (u8) INVALID_VALUE;
	return validate_number_u8( DAYS_IN_MONTH[iv] );
}

static
bool _leap_year(u16 y)
{
	bool y1 = false, y2 = false, y3 = false;
	y = validate_number_u16(y);
	y1 = (y %   4) == 0 ? true : false,
	y2 = (y % 100) != 0 ? true : false,
	y3 = (y % 400) == 0 ? true : false;
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
	y = validate_number_u16(y);
	passed_days  = (y - 1) * 365;
	passed_days += (y - 1) / 4;
	passed_days -= (y - 1) / 100;
	passed_days += (y - 1) / 400;
	return passed_days;
}

static
long _mm_passed_days(u8 m)
{
	u8 i = 0, tmp_passed = 0;
	long passed_days = 0;
	m--;
	while(i < m) {
		tmp_passed = _get_days_in_month(i);
		if( tmp_passed == INVALID_VALUE )
			break;
		passed_days += tmp_passed;	
		i++;
	}
	return passed_days;
}

long get_passed_days(u8 m, u16 y)
{
	u32 yy = 0, mm = 0;
   	bool leap_year = false;

   	y = validate_number_u16(y);
	m = validate_number_u8(m);
	leap_year = _leap_year(y);
	if(leap_year == true)
		_set_days_in_month(1, DAYS_LEAP_MONTH_TWO);
	else
		if( _get_days_in_month(1) != DAYS_NORM_MONTH_TWO )
			_set_days_in_month(1, DAYS_NORM_MONTH_TWO);

	yy = _yy_passed_days(y);
	mm = _mm_passed_days(m);

	return yy + mm;
}

u8 number_of_week(u8 d, u8 m, u16 y)
{
	long days = 0;
	d = validate_number_u8(d);
	m = validate_number_u8(m);
	y = validate_number_u16(y);
	days  = get_passed_days(m, y);
	days += d;
	return (days % DAYS_OF_WEEK);
}

void name_of_week(char* buffer, u8 week_number)
{
	switch(week_number) 
	{
		case 0: strncpy(buffer, "Sun", WEEK_OF_SIZE); break;
		case 1: strncpy(buffer, "Mon", WEEK_OF_SIZE); break;
		case 2: strncpy(buffer, "Tue", WEEK_OF_SIZE); break;
		case 3: strncpy(buffer, "Wed", WEEK_OF_SIZE); break;
		case 4: strncpy(buffer, "Thu", WEEK_OF_SIZE); break;
		case 5: strncpy(buffer, "Fri", WEEK_OF_SIZE); break;
		case 6: strncpy(buffer, "Sat", WEEK_OF_SIZE); break;
	}
}
