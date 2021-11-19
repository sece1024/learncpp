#include <stdio.h>

#define IN 1
#define OUT 0

/**
* time: 2021-11-19
* author: hgx
* describe:	print a histogram of the lengths of words in its input;
*/
int main()
{
	int c, nlength;
	int histogram[100 + 1];
	int i, j;
	
	for(i=0; i<101; i++)
		histogram[i] = 0;
		
	nlength = 0;
	
	while((c = getchar()) != EOF)
		if(c == ' ' || c == '\t' || c == '\n'){
			++histogram[nlength];
			nlength = 0;
		}
		else
			++nlength;
		
	
	for(i = 1; i < 101; i++){
		if(histogram[i] > 0){
			printf("%d\t| ",i);
			for(j = 0; j < histogram[i]; j++)
				putchar('*');
			putchar('\n');
		}	
		
	}

	return 0;
}
