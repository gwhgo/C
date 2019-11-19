#include <stdio.h>
/*
 * 对一个32位无符号整数做循环右移。
 * 所谓函数右移就是把低位移出去的部分再补到高位上去。
 * 例如rotate_right(0xdeadbeef,8)的结果应该是0xefdeadbe.
 */

unsigned int rotate_right(unsigned int x, int n){
	int i;
	unsigned int x_ = x;
	printf("*x_: %x\n",x_);
	for(i = 0; i < n;i++){
		unsigned int move = x_ & 1U;
		printf("*x_: %x\n",x_);
		printf("[-]move: %u\n",move);
		move = move << 31;
		printf("[+]move: %u\n",move);
		x_ = x_ >>1 | move;	
		printf("x_: 0x%x\n",x_);

	}
	return x_;
}

int main(void)
{
	printf("%x\n",rotate_right(0xdeadbeef,8));
}
