#include <stdio.h>
/*
 * 使用Euclid算法编写递归函数求两个正整数a和b的最大公约数(GCD).
 */

int gcd(int a, int b)
{
	int c;
	if( a < b ){
		c = a;
		a = b;
		b = c;
	}
	/* a > b */	
	c = a / b;
	int d = a % b;
	if (d == 0) return b;
	else {
		return gcd(b,d);	
	}
	
}
int main(void)
{
	printf("%d\n",gcd(1024,512));
}
