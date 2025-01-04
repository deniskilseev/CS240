#include <stdio.h>
//

int
main(int argc, char **argv) {
  printf("Welcome to the High Low game...\n");
	
	int high = 100;
	int low = 1; 
	int mid;
	char chr, none;
	
while (1) {
	high = 100;
	low = 1;
	printf("Think of a number between 1 and 100 and press <enter>");
	scanf("%c",&chr);
	while (high >= low) {
		mid = (high+low)/2;
		printf("Is it higher than %d? (y/n)\n",mid);		
		scanf("%c",&chr);
		getchar();
		if (chr != 'y' && chr != 'n') {
			printf("Type y or n\n");
			continue;
			}
		if (chr == 'y') {
			low = mid +1;
			}		
		if (chr == 'n') {
			high = mid -1;
			}
		}	
	printf("\n>>>>>> The number is %d\n",low);
	while (1) {
		printf("\nDo you want to continue playing (y/n)?\"");
		scanf("%c",&chr);
		getchar();
		if (chr != 'y' && chr != 'n') {
			printf("Type y or n\n");
			continue;
		}
		break;
	}
	if (chr == 'n') {
		printf("Thanks for playing!\n");
		break;
		}
	}
}
