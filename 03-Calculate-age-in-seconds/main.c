// Age calculator
// Written as part of /g/'s programming challenge
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>
#include <time.h>

void flush_readahead(void)
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

void read(const char* text, int min, int max, int * out)
{
	do
	{
		printf("%s", text);
		scanf("%d", out);
		flush_readahead();
	} while(*(out) <= min || *(out) >= max);

	return;
}

int main(int argc, char const *argv[])
{
	time_t now;
	struct tm birth_date;
	struct tm * time_info;
	int d = -1, m = -1, y = -1;

	/* Current time */
	time(&now);
	time_info = localtime(&now);

	printf("Calculate age in seconds - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Today is %d/%d/%d\n", time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);
	printf("Input your birth date as numbers:\n");

	/* Year */
	read("Year [1-Current]: ", 0, time_info->tm_year + 1900, &y);
	birth_date.tm_year = y - 1900;
	
	/* Month */
	read("Month    [1-12]: ", 0, 13, &m);
	birth_date.tm_mon = m - 1;

	/* Day */
	read("Day      [1-31]: ", 0, 32, &d);
	birth_date.tm_mday = d;
 
	birth_date.tm_sec = 0;
	birth_date.tm_min = 0;
	birth_date.tm_hour = 0;

	printf("Assumming you were born exactly at midnight\n");
	printf("%.f seconds passed since your birth.\n", difftime(now, mktime(&birth_date)) );

	return 0;
}