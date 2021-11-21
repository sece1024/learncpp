# C Programming

## IO

### EOF

- `EOF` is an integer defined in `<stdio>`, but the specific numeric value dosen't matter as long as it is not the same as any `char` value

## Function

### Arguments - Call by Value

> In C, all function arguments are passed "by value."
>
> When the name of an array is used as an argument, the value passed to the function is the location or address of the beginning of the array - there is no copying of array elements.



## Variable

### External variable

> External variable must be defined, exactly once outside of any function;
>
> The variable must also be declared in each function that wants to access it;
>
> The declaration may be an explicit `extern` statement ot may be implicit from context.

- The `extern` declaration can be omitted, if the definition of the external variable occurs in the source file before its use in a particular function.
- 

```c
/**
* time: 2021-11-21
* author: hgx
* describe:	print the longest input line; use external variable
*/ 

#include <stdio.h>
#define MAXLINE 1000		/* maximum input line length */

int max;					// maximum length seen so far
char line[MAXLINE];			// current input line
char longest[MAXLINE];		// longest line save here

int getline(void);
void copy(void);


int main()
{
	int len;				// current line length
	extern int max;			// maximum length seen so far
	extern char longest[];


	
	max = 0;
	while ((len = getline()) > 0)
		if (len > max){
			max = len;
			copy();
		} 
	if (max > 0)			// there was a line 
		printf("%s", longest);
	return 0;
}
/* getline: read a line into s, return length*/
int getline()
{
	int c, i;
	extern char line[];
	for (i = 0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	
	return i;
		
}
/* copy: copy 'from' into 'to'; assume to is big enough */
void copy()
{
	int i;
	extern char line[], longest[];
	i = 0;
	while ((longest[i] = line[i]) != '\0')
		++i;
}
```

### Enumeration

> A enumeration is a list of constant integer values, as in
>
> `enum boolean {NO, YES};`
>
> The first name in an enum has value 0, the next 1, and so on, explicit values are specified.