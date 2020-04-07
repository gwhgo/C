/* C标准库中生成伪随机数的是rand函数，使用这个函数需要包含头文件stdlib.h。rand函数没有参数，返回值是一个介于0和RAND_MAX之间的接近均匀分布的整数。RAND_MAX是该头文件中的一个常量，在不同平台上由不通的取值，但可以肯定是一个非常大的整数。通常我们用到的随机数是限定在某个取值范围之中的，例如 0 ~ 9,而不是 0 ~ RAND_MAX,我们可以用%运算符处理rand函数的返回值。*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define N 100


int a[N];

void gen_random(int upper_bound)
{
	for(int i = 0; i < N; i++)
		a[i] = rand() % upper_bound;
}

int howmany(int value)
{
	int count = 0;
	for(int i = 0; i < N; i++)
		if (a[i] == value) ++count;
	return count;
}

void print_random()
{
	int i;
	for(int i = 0; i < N;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int main(void)
{
	/* In the C language, all code that is executed at runtime must be inside a function. Put the call to `srand()` inside an init function.*/
	srand(time(NULL));
	int histogram[10] = {0};
	gen_random(10);

	for (int i = 0; i < N; i++)
		histogram[a[i]]++;

	/*	
	printf("value\thow many\n");
	for(int i = 0; i < 10; i++)
		printf("%d\t%d\n",i,howmany(i));
	*/

	for (int i = 0; i < 10; i++)
		printf("%d ",i);
	
	printf("\n\n");
	int count = N;
	while(1)
	{
		for (int i = 0; i < 10; i++)
			if (histogram[i] !=  0) {
				printf("* ");
				histogram[i]--;
				count--;
			}
			else printf("  ");
		printf("\n");
		if (count == 0) break;
	}
	return 0;
}
