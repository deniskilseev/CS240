
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    
    int i;
    char temp[17];
    int wordIndex = 0;
    for (i = 0; i < len; i++) {
    	if (i % 16 == 0) {
		fprintf(fd, "0x%016lX: ", (unsigned long) (p+i));
		wordIndex = 0;
	}
       	// Print address of the beginning of p. You need to print it every 16 bytes	
	
	int c = p[i]&0xFF; 
	// Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.

        // Print first byte as hexadecimal
        fprintf(fd, "%02X ", c);
	if (c >= 32 && c < 127) {
		temp[wordIndex++] = (char) c;
	}
	else {
		temp[wordIndex++] = '.';
	}
	if (wordIndex == 16) {
		temp[wordIndex] = '\0';
		fprintf(fd," %s\n",temp);
	}
    }
    if (wordIndex != 16) {
	    temp[wordIndex] = '\0';
    	for (int i = 0; i < 16-wordIndex; i++) {
		fprintf(fd,"   ");
	}
	fprintf(fd, " %s\n", temp);

    }
}

