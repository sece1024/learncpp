#include <stdio.h>

#define IN 1
#define OUT 0

/**
* time: 2021-11-19
* author: hgx
* describe:	print input one word per line;
*/
int main()
{
	int c;
	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\t')
			c = '\n';
		
		putchar(c);
	}
}
