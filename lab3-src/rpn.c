
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {

	double a,b,c;
	FILE *fd;
	stack_clear();
	fd = fopen(fileName, "r");
	char * word;
	while (word = nextword(fd)) {
		if (strcmp(word,"*") == 0
		|| strcmp(word,"/") == 0
		|| strcmp(word,"+") == 0
		|| strcmp(word,"-") == 0
		|| strcmp(word,"sin") == 0
		|| strcmp(word,"cos") == 0
		|| strcmp(word, "pow") == 0
		|| strcmp(word, "log") == 0
		|| strcmp(word, "exp") == 0) {
			
			switch (word[0]) {
				case ('*'):
					a = stack_pop();
					b = stack_pop();
					c = a * b;
					stack_push(c);
					break;
				case '/':
	                                a = stack_pop();
                                        b = stack_pop();
                                        c = b / a;
                                        stack_push(c);
                                        break;
				case '+':
					a = stack_pop();
                                        b = stack_pop();
                                        c = a + b;
                                        stack_push(c);
                                        break;
				case '-':
	 	                        a = stack_pop();
                                        b = stack_pop();
                                        c = b - a;
                                        stack_push(c);
                                        break;
				case 's':
					a = stack_pop();
					c = sin(a);
					stack_push(c);
					break;
				case 'c':
					a = stack_pop();
					c = cos(a);
					stack_push(c);
					break;
				case 'p':
					a = stack_pop();
					b = stack_pop();
					c = pow(b,a);
					stack_push(c);
					break;
				case 'l':
					a = stack_pop();
					c = log(a);
					stack_push(c);
					break;
				case 'e':
					a = stack_pop();
					c = exp(a);
					stack_push(c);
					break;
			}
		}
		else if (strcmp(word,"x")==0){
			stack_push(x);	
		}
		else {
			stack_push(atof(word));
		}
	}
	if (stack_top() == 1) {
		return stack_pop();
	}
	else if (stack_top() < 1) {
		printf("Stack underflow\n");
		exit(0);
	}
	else {
		printf("Elements remain in the stack\n");
		exit(0);
	}
}

