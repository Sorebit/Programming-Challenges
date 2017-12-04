// Triangle number calculator
// Written as part of /g/'s programming challenge
//
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Flush input buffer
void flush_readahead(void)
{
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

// Print some text, then read to tr of specified type from stdin 
// Repeat untill valid
void input(char* text, char* type, void* tr)
{
	int err;
	do
	{
		printf("%s", text);
		err = scanf(type, tr);
		flush_readahead();
	} while(!err);
}

int main(int argc, char const *argv[])
{	
	int n;

	// Greeting
	printf("Triangle number calculator - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n\n");

	input("Input number of dots per side: ", "%d", &n);

	printf("Total amount of dots in this triangle is " BLU "%d" RESET"\n", (n*(n + 1))/2);

	return 0;
}