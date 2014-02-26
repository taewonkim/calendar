#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "calendar.h"

int main(int argc, char** argv)
{
	int yy = 0, mm = 0, dd = 0;
	u8  week_number = 0;
	char* week_name = (char *) malloc( WEEK_OF_SIZE );

	printf("YYYY = ");
	scanf("%d", &yy);
	if(yy == 0)
	{
		fprintf(stderr, "Error. \"YYYY\" is not valid Value. (EX: 2014)\n");
		return INVALID_VALUE;
	}
	else
	{
		if( yy < 1970 || yy > 2020 )
		{
			fprintf(stderr, "Error. \"YYYY\" is grater equal 1970 and less equal 2020.\n");
			return INVALID_VALUE;
		}
	}

	printf("  MM = ");
	scanf("%d", &mm);
	if( mm == 0 )
	{
		fprintf(stderr, "Error. \"MM\" is not valid Value. (EX: 2)\n");
		return INVALID_VALUE;
	}
	else
	{
		if( mm < 1 || mm > 12 )
		{
			fprintf(stderr, "Error. \"MM\" is grater equal 1 and less equal 12.\n");
			return INVALID_VALUE;
		}
	}

	printf("  DD = ");
	scanf("%d", &dd);
	if( dd == 0 )
	{
		fprintf(stderr, "Error. \"DD\" is not valid Value. (EX: 26)\n");
		return INVALID_VALUE;
	}
	else
	{
		if( dd < 1 || dd > _get_days_in_month((mm-1)) )
		{
			fprintf(stderr, "Error. \"MM\" is grater equal 1 and less equal 12.\n");
			return INVALID_VALUE;
		}
	}

	//
	// Get a week number.
	// When return this function,
	// follow you see number.
	// It means next comment (split dash character).
	//
	// 0 - Sunday    (일요일)
	// 1 - Monday    (월요일)
	// 2 - Tuesday   (화요일)
	// 3 - Wednesday (수요일)
	// 4 - Thursday  (목요일)
	// 5 - Friday    (금요일)
	// 6 - Saturday  (토요일)

	week_number = number_of_week(dd, mm, yy);
	
	//
	// Get a week name.
	// 
	
	name_of_week(week_name, week_number);
	
	printf("WEEK = %s (%d)\n", week_name, week_number);

	free(week_name);
	return 0;
}
