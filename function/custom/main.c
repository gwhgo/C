#include <stdio.h>

int main(void)
{
	printf("Three lines:\n");
	threeline();
	printf("Another three lines.\n");
	threeline();
	return 0;
}

void newline(void)
{
	printf("\n");
}

void threeline(void)
{
	newline();
	newline();
	newline();
}

/*
 * 以上代码能够编译通过，且运行。 
 * 但是编译器会报warning。
 * 这里涉及的规则为函数的隐式声明(Implicit Declaration). 
 * 在main函数中调用threeline时并没有声明它，编译器此时认为隐式声明了int threeline(void);
 * 隐式声明的函数返回类型都是int, 由于我们调用这个函数时没有传递任何参数，所以编译器认为这个函数声明的参数类型时void。编译器根据这些信息为函数调用生成相应的指令。
 * 当编译器接下来看到threeline函数的原型为void threeline(void),和先前隐式声明的返回值类型不符的时候，就会报警。
 * 不过我们并没有用到这个函数的返回值，所以执行结果仍然正确。
 * 但是，别这么写！！！！！！！
 */
