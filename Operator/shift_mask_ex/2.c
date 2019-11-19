#include <stdio.h>

unsigned int multiply(unsigned int x, unsigned int y)
{
	unsigned int sum = 0;
	int count = 0;
	while (y != 0){
		if ( y & 1U == 1 ) {
			sum += x * 1<<count;
		}	
		count++;
		y = y >>1;
	}	
	return sum;
}

int main(void)
{
	printf("%u\n",multiply(3,100));
	return 0;
}
