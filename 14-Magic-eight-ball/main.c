// Magic 8-ball
// Written as part of /g/'s programming challenge
// 
// Sorebit - https://github.com/Sorebit/
//
// The Magic 8 Ball is a toy used for fortune-telling or 
// seeking advice, developed in the 1950s and manufactured 
// by Mattel. It is often used in fiction, often for humor
// related to its giving very accurate, very inaccurate, 
// or otherwise statistically improbable answers.
// https://en.wikipedia.org/wiki/Magic_8-Ball

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;

char *ans[20] = {
	// Positive
	"It is certain",
	"It is decidedly so",
	"Without a doubt",
	"Yes, definitely",
	"You may rely on it",
	"As I see it, yes",
	"Most likely",
	"Outlook good",
	"Yes",
	"Signs point to yes",
	// Neutral
	"Reply hazy try again",
	"Ask again later",
	"Better not tell you now",
	"Cannot predict now",
	"Concentrate and ask again",
	// Negative
	"Don't count on it",
	"My reply is no",
	"My sources say no",
	"Outlook not so good",
	"Very doubtful",
}; 

int spaces(char *c)
{
	int len;
	// Calculate the length of text
	for(len = 0; c[len] != '\0'; ++len);
	// Calculate spaces needed to center it
	return (27 - len) / 2 - 1;
}

char* color(int n)
{
	if(n == -1)
		return "\033[0m"; // Reset color
	if(n < 10)
		return "\033[0;32m"; // Green - positive
	else if(n < 15)
		return "\033[0;34m"; // Blue - neutral
	else
		return "\033[0;31m"; // Red - negative
}

int main(int argc, char const *argv[])
{
	char c;  // Character buffer for getcha	
	int s;   // Space count to center the quote
	int i;   // Index of answer
	char *a; // Answer

	srand(time(NULL));
	
	printf("Magic 8-ball - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Ask a question and then shake the ball to find out the answer\n");

	while(true)
	{
		printf("Enter - shake the ball, Q - quit\n");
		while((c = getchar()) != '\0' && c != '\n')
			if(c == 'q') return 0;

		// Select a random answer
		i = rand() % 20;
		a = ans[i];
		s = spaces(a);
		printf("===========================\n");
		printf("    The magic ball says:\n");
		// Center the answer
		for(; s > 0; --s) printf(" ");
		// Print the answer
		printf("\"%s%s%s\"\n", color(i), a, color(-1));
		printf("===========================\n\n");

	}

	return 0;
}