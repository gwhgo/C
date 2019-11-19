#include <stdio.h>

int main(void)
{
	//取出8~15位
	unsigned int a, b, mask = 0x0000ff00;
	a = 0x12345678;
	b = (a & mask) >> 8;
	//以下写法也可以得出同样的效果
	//b =(a >> 8) & ~(~0U << 8);
	printf("%x\n",b);
}
