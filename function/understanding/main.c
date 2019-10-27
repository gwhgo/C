#include <stdio.h>
#include <math.h>

void print_logarithm(double x)
{
	if (x <= 0.0){
		printf("Positive numbers only, please.\n");
		return;
	}
	printf("The log of x is %f\n", log(x));
}

int main(void)
{
	print_logarithm(100);
}
