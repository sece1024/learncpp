#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	count characters in input;
*/
int main()
{
	long nc;
	nc = 0;
	while (getchar() != EOF)
		++nc;
	printf("%ld\n", nc);
	
	return 0;
}
