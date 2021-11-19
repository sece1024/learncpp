#include <stdio.h>

#define IN 1
#define OUT 0

/**
* time: 2021-11-19
* author: hgx
* describe:	count line, words, and characters in input;
*/
int main()
{
	int c, nl, nw, nc, state;
	state = OUT;
	nl = nw = nc = 0;
	while((c = getchar()) != EOF){
		++nc;
		if(c == '\n')
			++nl;
		if(c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if(state == OUT){
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d", nl, nw, nc);
}
