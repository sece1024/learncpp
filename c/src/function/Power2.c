#include <stdio.h>

/**
* time: 2021-11-20
* author: hgx
* describe:	test power function
*/ 

int power(int m, int n);

int main()
{
//	printf("Hello, world!\n");
	int i;
	for (i = 0; i < 10; ++i)
		printf("%d\t%d\t%d\n", i, power(2, i), power(-3, i));
	
	return 0;
}

int power(int base, int n)
{
	int p;
	
	for(p = 1; n > 0; --n){
		p = p * base;
	}
	return p;
}
