// Password generator
// Written as part of /g/'s programming challenge
//
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef enum {false, true} bool;

int len;
int r;
int nums;
char buf[3];
char str[256];
bool upc;

int main(int argc, char const *argv[])
{

	// Set seed based on time
	srand(time(NULL));

	printf("Password generator - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n");

	// Input length of password
	printf("Input ength of passowrd (max 256): ");
	scanf("%d", &len);

	// Numbers
	printf("How many numbers? (max %d): ", len);
	scanf("%d", &nums);
	nums = min(nums, len);

	// Uppercase
	printf("Use uppercase letters? [y/n] ");
	scanf("%s", buf);
	upc = (buf[0] == 'y' || buf[0] == 'Y');

	// Generate random chars
	for(int i = 0; i < len; ++i)
	{
		str[i] = rand() % 26 + 'a';
		if(upc && rand() % 3 == 0)
			str[i] -= 'a' - 'A';
	}
	
	// Add numbers
	for(int i = 0; i < nums; ++i)
	{
		do
		{
			r = rand() % len;
		} while(str[r] < 'a');
		str[r] = rand() % 10 + '0';
	}

	// Print generated password
	printf("\n%s\n", str);

	return 0;
}