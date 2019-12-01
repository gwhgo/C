#include <stdio.h>
/*
 * 枚举类型的成员是常量，它们的值由编译器自动分配
 * 例如：
 * enum coordiante_type { RECTANGULAR, POLAR };
 * RECTANGULAR 表示 常量 0。
 * POLAR 表示 常量 1 。
 * 如果不希望从0开始分配，可以使用：
 * enum coordiante_type {RECTANGULAR=1,POLAR};
 */
/* 虽然结构体的成员名和变量名不在同一命名空间中，但枚举的成员名却和变量名在同一命令空间中，所以会出现命名冲突。*/
enum coordiante_type { RECTANGULAR=1, POLAR };
/*
struct complex_struct {
	enum coordinate_type t;
	double a,b;
};

struct complex_struct make_from_real_img(double x, double y)
{
	struct complex_struct z;
	z.t = RECTANGULAR;
	z.a = x;
	z.b = y;
	return z;
}

struct complex_struct make_from_mag_ang(double r, double A)
{
	struct complex_struct z;
	z.t = POLAR;
	z.a = r;
	z.b = A;
	return z;
}
*/


int main(void){
	//struct complex_struct cplx = make_from_real_img(1.0,2.0);
	printf("%d\n",RECTANGULAR);
	printf("%d\n",POLAR);
}

