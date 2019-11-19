#include <stdio.h>

int main(void)
{
	/*将8~15位置1 */
	unsigned a, b, mask = 0x0000ff00;
	a = 0x12345678;
	b = a | mask;  /* 0x1234ff78 */
	printf("%x\n",b);
}
