#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "calendar.h"

int main(int argc, char** argv)
{
	int yy = 0, mm = 0, dd = 0;
	int week_number = 0;
	char* week_name = (char*) malloc( WEEK_OF_SIZE );

	printf("YYYY = ");
	scanf("%d", &yy);
	printf("  MM = ");
	scanf("%d", &mm);
	printf("  DD = ");
	scanf("%d", &dd);

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
	name_of_week(week_name, week_number);

	printf("WEEK = %s (%d)\n", week_name, week_number);

	free(week_name);
	return 0;
}
