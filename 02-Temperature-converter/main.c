// Temperature converter
// Written as part of /g/'s programming challenge
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

void flush_readahead(void)
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char const *argv[])
{
	char in_unit;
	float in_temp = 0.0;
	
	// Greeting
	printf("Temperature converter - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n\n");
	
	// Wait for the user to input right
	while(in_unit != 'C' && in_unit != 'K' && in_unit != 'F')
	{
		printf("Input temperature (float) [C/F/K]: ");
		scanf("%f %c", &in_temp, &in_unit);
		in_unit = (in_unit > 'a') ? in_unit - 32 : in_unit;
		flush_readahead();
	}

	// Calculate and show different units
	printf("\n%.2f %c is:\n", in_temp, in_unit);

	switch(in_unit)
	{
		case 'C':
			printf("%.2f K\n", in_temp + 273.15);
			printf("%.2f F\n", in_temp * 1.8 + 32);
			break;
		case 'K':
			printf("%.2f C\n", in_temp - 273.15);
			printf("%.2f F\n", (in_temp - 273.15) * 1.8 + 32);
			break;
		case 'F':
			printf("%.2f C\n", (in_temp - 32) / 1.8);
			printf("%.2f K\n", ((in_temp - 32) / 1.8) + 273.15);
			break;
	}

	return 0;
}