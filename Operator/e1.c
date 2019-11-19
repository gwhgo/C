#include <stdio.h>

int main(void)
{
	//'0b11001111111111111111111111110011'
	int i = 0xcffffff3;
	//unsigned int
	printf("%x\n",0xcffffff3 >> 2);
	//signed int
	printf("%x\n",i >> 2);
}
