#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	copy input to output, replacing each string of one or more blanks by a single blank;
*/
#define OUTPUT 0
#define NOTOUTPUT 1
int main()
{
	char c;
	int flag = OUTPUT;
	while ((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\t')
			if(flag == NOTOUTPUT)
				{}
			else
			{
				flag = NOTOUTPUT;
				putchar(c=='\t'?' ':c);
			}
				
		else{
			flag = OUTPUT;
			putchar(c);
		}
		
	}
		
	
	return 0;
}
