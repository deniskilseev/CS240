
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void filedump(char * p , int len) {
}

int
main(int argc, char **argv) {
	char *k;
	char * filename = argv[1];
	int len = INT_MAX;
	if (argc == 3) {
		long maxbytes = strtol(argv[2], &k,10);
		len = (int) maxbytes;
	}
    
    char * p;	
    FILE *file;
    file = fopen(filename,"r");
    if (file == NULL) {
    	printf("Error opening file \"%s\"\n",filename);
	return -1;
    }
    int i;
    char temp[17];
    int wordIndex = 0;
    int memory = 0;
    for (i = 0; i < len; i++) {
	int c = fgetc(file)&0xFF;
	if ((char) c == EOF) {
		break;
	}
        if (i % 16 == 0) {
                printf("0x%016lX: ", (unsigned long) (memory));
		memory += 16;
                wordIndex = 0;
        }
        // Print address of the beginning of p. You need to print it every 16 bytes     
        // Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.

        // Print first byte as hexadecimal
        printf("%02X ", c);
        if (c >= 32 && c < 127) {
                temp[wordIndex++] = (char) c;
        }
        else {
                temp[wordIndex++] = '.';
        }
        if (wordIndex == 16) {
                temp[wordIndex] = '\0';
                printf(" %s\n",temp);
        }
    }
    if (wordIndex != 16) {
            temp[wordIndex] = '\0';
        for (int i = 0; i < 16-wordIndex; i++) {
                printf("   ");
        }
        printf(" %s\n", temp);

    }
}


