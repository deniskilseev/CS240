
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	char * t;
	int size = 0;
    	for (t = s; *t != '\0'; t++) {
		size++;
    	}
    	return size;
}

char * mystrcpy(char * dest, char * src) {
	char *memory = dest;
	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return memory;
}

char * mystrcat(char * dest, char * src) {
	char *memory = dest;
	while (*dest!= '\0') {
		dest++;
	}

	while (*src!= '\0') {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return memory;
}

int mystrcmp(char * s1, char * s2) {
	while (*s1) {
		if (*s1 != *s2) {
			break;
		}
		s1++;
		s2++;
	}
	int value = (int)(*s1) - (int)(*s2);
	if (value == 0) {
		return 0;	
	}
	if (value > 0) {
		return 1;
	}
	if (value < 0) {
		return -1;
	}
}

int plscompare(char *haypart, char *needlepart)
{
    while (*haypart && *needlepart)
    {
        if (*haypart != *needlepart) {
            return 0;
        }
 
        haypart++;
        needlepart++;
    }
 
    return (*needlepart == '\0');
}



char * mystrstr(char * hay, char * needle) {
    while (*hay != '\0')
    {
        if ((*hay == *needle)) {
		if (plscompare(hay,needle)) {
            return hay;
	    }
        }
        hay++;
    }
    return NULL;
}

char * mystrdup(char * s) {
	char *news;
	char *p;
	news = malloc(mystrlen(s)+1);
	p = news;
	while (*s) {
		*p = *s;
		p++;
		s++;
	}
	*p = '\0';
	return news;
}

char * mymemcpy(char * dest, char * src, int n) {
	char *p;
	p = dest;
	for (int i = 0; i < n; i++) {
		*p = *src;
		p++;
		src++;
	}
	return dest;
}

