#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char curDigToLetter(int curDig) {
        char extrachars[] = "0123456789ABCDEFGHIJKLMNOP";
        return extrachars[curDig];
    }

void main(int argc, char* argv[]) {

	char extrachars[] = "ABCDEFGHIJKLMNOP";
	if (argc != 4
	|| atoi(argv[1]) > 25
	|| atoi(argv[1]) < 2
	|| atoi (argv[2]) > 25
	|| atoi (argv[2]) < 2
	) {
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
		return NULL;
	}
	long basefrom = strtol(argv[1], NULL, 10);
	long baseto = strtol(argv[2], NULL, 10);
	long number = strtol(argv[3], NULL, basefrom);
        printf("Number read in base %ld: %s\n", basefrom, argv[3]);

        for (int i = 0; i < strlen(argv[3]); i++) {
                if (argv[3][i] > curDigToLetter(basefrom)) {
			printf("Wrong digit in number.\n");
			return 0;
		}
        }

	int returnNumber = 0;
	int numberDec = 0;
	int multiplyBy = 1;

	printf("Converted to base 10: %ld\n", number);
	
	multiplyBy = 1;
	char answer[] = "";
	while (!(number < baseto)) {
		int curDig = number % baseto;
		char dig = curDigToLetter(curDig);
		number = number / baseto;
		strncat(answer,&dig,1);
	}
	char dig = curDigToLetter(number);
	strncat(answer, &dig,1);
	
	//Number read in base 10: 100077900
	//Converted to base 10: 100077900
	//Converted to base 25: A64OG0
	strrev(answer);	
	printf("Converted to base %ld: %s\n", baseto, answer);
}
