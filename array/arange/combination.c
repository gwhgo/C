#include <stdio.h>
#define N 4
#define M 2

int a[N];

void init(int a[])
{
	for(int i = 0; i < N; i++)
		a[i] = i+1;	
}

void print(int a[])
{
	for(int i = 0; i < M-1;i++)
		printf("%d-",a[i]);
	printf("%d\n",a[M-1]);
}
/* Function to swap values at two pointers */
void swap(int* x, int* y) 
{ 
	int temp; 
	temp = *x; 
	*x = *y; 
	*y = temp; 
} 

void comb(int* a,int l, int r, int m)
{
	if ( r == M){
		print(a);	
		return;
	}
	for(int i = l; i < r;i++)
	{
		comb(a,l+1,r-i,m-1);	
		swap(a+l,a+r);
	}	
}
int main(void)
{
	init(a);
	comb(a,0,N,M);	
}
