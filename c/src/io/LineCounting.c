#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	count lines in input;
*/
int main()
{
	int c, nl;

	nl = 0;
	char a = '\\';
//	printf("%d = %c\n",a,a);
	while ((c = getchar()) != EOF)
	// count newlines, blanks, tabs
		if(c == '\n' || c ==' ' || c=='\t')
			++nl;
	
	printf("%d\n", nl);
	
	return 0;
}
