#include <stdio.h>
/*
 * fib(0) = 1
 * fib(1) = 1
 * fib(n) = fib(n-1) + fib(n-2)
 */

int fib(int n)
{
	if(n == 0 || n == 1) return 1;
	else
	{
		return fib(n-1) + fib(n-2);
	}
}
int main(void)
{
	printf("%d\n",fib(10));
}
