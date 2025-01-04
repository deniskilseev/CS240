
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{
	double top_value;
	top_value = stack[top];
	top--;
	return top_value;
}

void stack_push(double val)
{
	top++;
	stack[top] = val;

}

void stack_print()
	{
	printf("Stack:\n");
	if (stack_is_empty()) {
		printf("Stack is empty");
	}
	else {
		for (int i = 0 ; i < top ; i++) {
			printf("%d: %.6f\n",i,stack[i+1]);
		}
	}
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


