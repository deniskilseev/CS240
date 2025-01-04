
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lines=0;
	char * fileName = argv[1];
	FILE * fd = fopen(fileName,"r");
	if (fd == NULL) {
		printf("Couldn't open the file");
		exit(1);
	}

	while ((c=fgetc(fd))!=-1) {
		if (c == '\n') {
			lines++;
		}
	}
	printf("Program that counts lines.\n");
	printf("Total lines: %d\n",lines);
	fclose(fd);
	exit(0);
}
