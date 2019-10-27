#include <stdio.h>

struct complex_struct {double x,y;} z;
/* 结构体变量之间允许使用赋值运算符，同时也允许用一个结构体变量初始化另外一个结构体变量*/
/* 结构体也可以作为参数和返回值来传递 */
struct complex_struct add_complex(struct complex_struct  z1, struct complex_struct z2)
{
	z1.x = z1.x + z2.y;
	z1.y = z1.y + z2.y;
	return z1;
}

int main(void)
{
	double x = 3.0;
	z.x = x;
	z.y = 4.0;
	if (z.y < 0) printf("z=%f%fi\n",z.x,z.y);
	else printf("z=%f+%fi\n",z.x,z.y);
	/* 初始化， 如果 Intializer 中的数据比结构体的成员少，未指定的成员将用0来初始化 */
	struct complex_struct z1 = { x,4.0,};
	struct complex_struct z2 = { 3.0,};
	struct complex_struct z3 = { 0 };
	/* z1 = {3.0, 4.0} 是错误的,{}这种语法不能用于结构体的赋值*/
	
	/* Designated Initializer 时 C99引入的特性，用于初始化 稀疏 (Sparse) 结构体和稀疏数组很方便*/
	struct complex_struct z4 = { .y = 4.0 };

	/*使用函数进行结构体运算*/
	struct complex_struct z5 = add_complex(z1,z2);
	printf("%f\t%f\n",z5.x,z5.y);
	return 0;
}
