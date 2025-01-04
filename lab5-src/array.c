
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
	double max = *array;
	for (int i = 1; i < n; i++) {
		if (*(array+i) > max) {
			max = *(array+i);
		}
	}
	return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
        double min = *array;
        for (int i = 1; i < n; i++) {
                if (*(array+i) < min) {
                        min = *(array+i);
                }
        }
        return min;

}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
	double found;
 	for (int i = 0; i < n; i++) {
		if (min <= *(array+i) && *(array+i) <= max) {
			return i;
		}
	}
	return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (*(array+j)>*(array+j+1)) {
				double temp = *(array+j);
				*(array+j) = *(array+j+1);
				*(array+j+1) = temp;
			}
		}
	}
}

// Print array
void printArray(int n, double * array) {
	for (int i = 0; i < n; i++) {
		printf("%d:%f\n",i, *(array+i));
	}
}

