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

	week_number = number_of_week(dd, mm, yy);
	name_of_week(week_name, week_number);

	printf("WEEK = %s (%d)\n", week_name, week_number);

	free(week_name);
	return 0;
}
