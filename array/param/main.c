#include <stdio.h>

void foo(int a[5]){
	a[0] = 2;
	for(int i=0; i < 5;i++)
		printf("%d\n",a[i]);
}
int main(void)
{
	//int b[5] = {1,2,3,4,5};
	//foo(b);	
	int b[5]  = {1,2,3,4,5};
	int a[5];
	a = b;
	//foo(b);
	for(int i= 0;  i < 5; i++)
		printf("%d\n",a[i]);
}
