// Love calculator
// Written as part of /g/'s programming challenge
// 
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

// Looks like it is most commonly used as it is the simplest solution
int HashString(char *s)
{
	int v = 0;
	while(*s)
	{
		v += *s;
		s++;
	}
	return v;
}

int main(int argc, char const *argv[])
{
	char first[256];
	char second[256];
	printf("Love calculator - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Calculate love percentage between two names.\n");
	
	printf("Input first name:\n");
	scanf("%s", first);
	printf("Input second name:\n");
	scanf("%s", second);

	int percent = (HashString(first) + HashString(second)) % 101;

	printf("============================\n");
	printf("Your love percentage is %d%%\n", percent);

	// Additional text
	if(percent > 90)
		printf("Wow! That's a lot of love!\n");
	else if(percent > 70)
		printf("That's quite a lot of love!\n");
	else if(percent > 50)
		printf("It's still quite a bunch.\n");
	else if(percent > 30)
		printf("It's still love after all.\n");
	else if(percent > 10)
		printf("It could have been better...\n");
	else
		printf("Oh...\n");


	return 0;
}