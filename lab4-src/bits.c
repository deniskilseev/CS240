#include <stdio.h>


// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	for (int i = 31; i > -1; i--) {
		unsigned int mask = (1 << i);
		unsigned int y = (bitmap&mask);
		int bit = (y >> i);
		if (bit) {
			printf("1");	
		}
		else {
			printf("0");
		}
	}
	printf("\n");
	for (int i = 31; i > -1; i--) {
		printf("%d",i%10);
	}
	printf("\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	unsigned int mask = (1 << i);
	if (bitValue == 0) {
		mask = ~mask;
		*bitmap = *bitmap & mask;
	}
	else {
		*bitmap = *bitmap | mask;		
	}
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	unsigned int mask = (1 << i);
	unsigned int y = (bitmap&mask);
	int bit = (y >> i);
	return bit;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	int ones = 0;
	int zeros = 0;
	for (int i = 31; i > -1; i--) {
                unsigned int mask = (1 << i);
                unsigned int y = (bitmap&mask);
                int bit = (y >> i);
                if (bit) {
			ones++;
                        
		}
                else {
			zeros++;
                }
        }
	if (bitValue) {
		return ones;
	}
	else {
		return zeros;
	}

}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	int maxLen = 0;
	int curLen = 0;
        for (int i = 31; i > -1; i--) {
                unsigned int mask = (1 << i);
                unsigned int y = (bitmap&mask);
                int bit = (y >> i);
                if (bit) {
			curLen++;
			if (curLen > maxLen) {
				*position = i;
				maxLen = curLen;
			}
                }
                else {
                        curLen = 0;
                }
        }
	return maxLen;
}


