#include <stdio.h>

int main(void)
{
	/* 数组也可以像结构体一样进行初始化，未赋初值的元素也是用0来初始化的*/
	int count1[4] = {3,2,};
	for(int i = 0; i < 4; i++)
		printf("count[%d]=%d\n",i,count1[i]);
	/* 编译器会根据Initializer 有三个元素确定数组的长度为3 */
	int count2[] = {3,2,1};
	/* 利用C99的新特性也可以做 Memberwise Initializatioin*/
	int count3[4] = { [2] = 3 };
	for (int i = 0; i < 4; i++)
		printf("count[%d]=%d\n",i,count3[i]);
	return 0;
}
