
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	wordLength = 0;
	while((c=fgetc(fd))!=-1) {
			if  (c != ' ' && c!= '\r' && c != '\n' && c!= '\r') {
				word[wordLength++] = c;	
			}
			else {
				if (wordLength == 0) {
					continue;
				}
				word[wordLength++] = '\0';
				return word;
			}
	}
	return NULL;
}

