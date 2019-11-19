#include <stdio.h>

int main(void)
{
	unsigned int a, b, mask = 0x0000ff00;
	a = 0x12345678;
	b = a & ~mask; /* -x12340078 */
	printf("%x\n",b);
}
