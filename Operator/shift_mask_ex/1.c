/*
 * 统计一个无符号数的二进制表示中1的个数，函数原型是int countbit(unsigned int x);
 */

#include <stdio.h>

int countbit(unsigned int x){
	int count = 0;
	while (x!=0){
		if (x & 1U == 1)
			count ++;
		x = x >> 1;
	}
	return count;
}

int main(void)
{
	printf("bit count is %d\n",countbit(1U));
	return 0;
}
