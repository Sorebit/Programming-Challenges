// Temperature converter
// Written as part of /g/'s programming challenge
//
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

long long factorial(int n)
{
	if(n < 0)
		return -1;
	if(n == 0)
		return 1;
	return factorial(n - 1) * n;
}

int main(int argc, char const *argv[])
{
	// Input number
	int n;

	printf("Factorial - Sorbet\n");
	printf("Written as part of /g/'s programming chalenges\n\n");
	printf("Input number to calculate the factorial of:\n");

	scanf("%d", &n);
	long long f = factorial(n);
	if(n > 20)
		printf("The number is too big to compute!\n");
	else
		printf("%lld\n", f);
	return 0;
}