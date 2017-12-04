// Pascal's and Sierpinki's triangle generator
// Written as part of /g/'s programming challenge
//
// Sorebit - https://github.com/Sorebit/

#include <stdio.h>

#define min(a, b) ((a < b) ? (a) : (b))
#define MAXN       1000
#define MODE_CALC  0
#define MODE_SHOW  1 
#define MODE_SIERP 2

unsigned long long tri[MAXN][MAXN];

void triangle(int sz, int mode)
{
	if(mode == MODE_SHOW)
		printf("PASCAL'S TRIANGLE\n");
	else if(mode == MODE_SIERP)
		printf("SIERPINSKI'S TRIANGLE (PASCAL'S TRIANGLE %% 2)\n");
	for(int i = 0; i < sz; ++i)
	{
		for(int j = 0; j <= i; ++j)
		{
			if(mode == MODE_SHOW)
				printf("%llu ", tri[i][j]);
			else if(mode == MODE_SIERP)
				printf("%c ", (tri[i][j] % 2) ? '#' : ' ');
			else
			{			
				if(j == 0 || j == i)
					tri[i][j] = 1;
				else
					tri[i][j] = tri[i - 1][j] + tri[i - 1][j - 1];
			}
		}
		if(mode == MODE_SHOW || mode == MODE_SIERP)
			printf("\n");
	}
	if(mode == MODE_SHOW || mode == MODE_SIERP)
		printf("\n");
}


int main(int argc, char const *argv[])
{
	int sz;
	printf("Pascal's triangle generator - Sorbet.\n");
	printf("Written as part of /g/'s programming chalenges.\n");
	printf("Input size of the triangle (30 is still readable as for me):\n");
	scanf("%d", &sz);
	sz = min(sz, MAXN);

	triangle(sz, MODE_CALC);
	triangle(sz, MODE_SHOW);
	triangle(sz, MODE_SIERP);

	return 0;
}