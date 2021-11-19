#include<stdio.h>

/**
* time: 2021-11-19
* author: hgx
* describe:	copy input to output
*/
int main()
{
	int c;
	// EOF: end of file
//	printf("add = %p\tEOF = %ld\n, ",EOF);

	

	// 1st version
	/*
	c = getchar();
	while (c != EOF){
		putchar(c);
		c = getchar();
	}
	*/
	// 2nd version
	printf("%d\n",getchar() != EOF);
	while((c = getchar()) != EOF)
		
		putchar(c);
	
	return 0;
 } 
