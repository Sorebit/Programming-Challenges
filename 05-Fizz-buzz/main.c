// FizzBuzz
// Written as part of /g/'s programming challenge
// 
// Sorebit - https://github.com/Sorebit/
//
// Fizz buzz is a group word game for children to teach them 
// about division. Players take turns to count incrementally, 
// replacing any number divisible by three with the word "fizz", 
// and any number divisible by five with the word "buzz".
// https://en.wikipedia.org/wiki/Fizz_buzz

#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("FizzBuzz - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Calculate love percentage between two names.\n");
	
	int n;
	printf("How many times do you want me to fizz and buzz?\n");
	scanf("%d", &n);

	for(int i = 1; i <= n; ++i)
	{
		if(i % 3 == 0)
			printf("Fizz");
		if(i % 5 == 0)
			printf("Buzz");
		if((i % 3) && (i % 5))
			printf("%d", i);
		printf("\n");
	}

	return 0;
}