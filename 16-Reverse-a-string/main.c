// Temperature converter
// Written as part of /g/'s programming challenge
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

void swap(char *a, char *b)
{
	char c;
	c = *a;
	*a = *b;
	*b = c;
}

int main(int argc, char const *argv[])
{
	// Char buffer
	char c;
	// String
	char str[1024] = "";
	// Length of string
	int len = 0;

	printf("Reverse a string - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n\n");
	printf("Input string to be reversed:\n");	

	// Read string
	while((c = getchar()) != '\0' && c != '\n')
		str[len++] = c;
	// Reverse it
	for(int i = 0; i < len / 2; ++i)
		swap(&str[i], &str[len-i-1]);
	// Print reversed
	printf("%s\n", str);
	return 0;
}