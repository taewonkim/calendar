#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_VALUE	-1

#define WEEK_OF_SIZE	3

enum BOOL {
	false, true
};

typedef enum BOOL bool;

int DAYS_IN_MONTH[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static
int _length_days_in_month()
{
	return sizeof(DAYS_IN_MONTH) / sizeof(int);
}

static
bool _overflow_days_in_month(int index)
{
	int count = _length_days_in_month();
	count--;
	return (index > count) ? true : false;
}

static
bool _underflw_days_in_month(int index)
{
	return (index <     0) ? true : false;
}

static 
void _set_days_in_month(int index, int value)
{
	if(_underflw_days_in_month(index) == true)
		return ;
	if(_overflow_days_in_month(index) == true)
		return ;
	DAYS_IN_MONTH[index] = value;
}

static
int _get_days_in_month(int index)
{
	if(_underflw_days_in_month(index) == true)
		return INVALID_VALUE;
	if(_overflow_days_in_month(index) == true)
		return INVALID_VALUE;
	return DAYS_IN_MONTH[index];
}

static
bool _leap_year(int y)
{
	bool y1 = (y % 4)   == 0 ? true : false,
		 y2 = (y % 100) != 0 ? true : false,
		 y3 = (y % 400) == 0 ? true : false;
	if( ((y1 == true) || (y2 != true)) && 
		 (y3 == true))
		return true;
	else
		return false;
}

static 
long _yy_passed_days(int y)
{
	long passed_days = 0;
	passed_days  = (y - 1) * 365;
	passed_days += (y - 1) / 4;
	passed_days -= (y - 1) / 100;
	passed_days += (y - 1) / 400;
	return passed_days;
}

static
long _mm_passed_days(int m)
{
	int i = 0, tmp_passed = 0;
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

static
long get_passed_days(int m, int y)
{
	long yy = 0, mm = 0;
   	bool leap_year = false;

	leap_year = _leap_year(y);
	if(leap_year == true)
		_set_days_in_month(1, 29);
	else
		_set_days_in_month(1, 28);

	yy = _yy_passed_days(y);
	mm = _mm_passed_days(m);

	return yy + mm;
}

static
int number_of_week(int d, int m, int y)
{
	long days = get_passed_days(m, y);
	return (days + d) % 7;
}

static
void name_of_week(char* buffer, int wn)
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

int main(int argc, char** argv)
{
	int yy = 0, mm = 0, dd = 0;
	int wn = 0;
	char* wm = (char*) malloc( WEEK_OF_SIZE );

	printf("YYYY = ");
	scanf("%d", &yy);
	printf("  MM = ");
	scanf("%d", &mm);
	printf("  DD = ");
	scanf("%d", &dd);

	wn = number_of_week(dd, mm, yy);
	name_of_week(wm, wn);

	printf("WEEK = %s (%d)\n", wm, wn);

	free(wm);
	return 0;
}
