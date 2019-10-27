#include <stdio.h>

int factorial(int n)
{
	if (n == 0) return 1;
	else{
		return n*factorial(n-1);
	}
}
		
int main(void)
{
	int argument = 10;
	printf("factorial of %d is %d\n",argument,factorial(10));
}
