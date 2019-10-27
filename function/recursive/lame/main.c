#include <stdio.h>
/*
 * Lame定理
 * 如果Euclid算法需要k步来计算两个数的GCD,那么两个数中较小的一个必然 大于等于 Fibonacci数列的第K项
 * Refer to : < Structure and Interpretaion of Compouter Programs>
 */
int k_gcd = 0;
int k_factorial = 0;

int gcd(int a, int b)
{
	k_gcd++;
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
	return 0;					
}
