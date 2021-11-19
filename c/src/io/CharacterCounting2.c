#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	count characters in input;
*/
int main()
{
	double nc;

	for (nc=0; getchar() != EOF; ++nc){}
	
	printf("%.0f\n", nc);
	
	return 0;
}
