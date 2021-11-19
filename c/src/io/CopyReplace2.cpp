#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	copy input to output, replacing each tab by \t, each backspace by \b, and each backslash by \\;
*/
#define OUTPUT 0
#define NOTOUTPUT 1
int main()
{
	char c;
	int flag = OUTPUT;
	while ((c = getchar()) != EOF)
	{
		if(c == '\t'){
			putchar('\\');
			c = 't';
		}
		if(c == '\b'){
			putchar('\\');
			c = 'b';
		}
		
		if(c == '\\')	c = '\\';
		
		putchar(c);
	}
	return 0;
}
