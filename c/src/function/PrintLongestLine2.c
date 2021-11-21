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
int mstrlen(char s[]);		// return length of s

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
		printf("%s\nlength = %d", longest, mstrlen(longest));
	
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

/* mstrlen: length of string*/
int mstrlen(char s[])
{
	int i = 0;
	while (s[i] != '\0'){
		++i;
	}
	return i;
}
