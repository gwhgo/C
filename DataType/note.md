# 整型
- Implementation Undefined:
	C标准没有明确规定char是有符号还是无符号的，但要求编译器必须做出明确规定，并卸载编译器的文档中。
- Unspecified
	C标准没有明确规定按哪种方式处理，编译器可以自己决定，并且也不必卸载编译器的文档中。这样即使用一个编译器的不同版本来编译也可能得到不同的结果。
- Undefined
	Undefined的情况完全是不确定的，C标准没规定怎么处理，编译器可能也没规定，甚至也没做出错处理，有很多Undefined的情况编译器是检查不出来的，最终会导致运行时错误，比如数组访问越界就是Undefined的。

除了char型在C标准中明确规定占一个字节之外，其他整型占几个字节都是Implementation Defined。通常的编译器实现遵守ILP32或LP64规范。

类型		| ILP32  |  LP64
char		|  8 	 |   8
short		|  16	 |  16
int			|  32	 | 	32
long		|  32 	 |  64
long long	|  64    |  64
指针 		|  32    |  64

 
平台 x86/Linux/gcc 遵循ILP32 并且char是有符号的。
C语言的常量有整数常量、字符常量、枚举常量和浮点数常量四种。其实字符常量和枚举常量的类型都是int型。

整数常量还可以在末尾加u或U表示"unsigned", 加l或 L 表示"long"，加ll或LL表示"long long"。
例如, 0x1234U、98765ULL等。但事实上u,l,ll这几种后缀和上面讲的unsigned,long,long long关键字并不是一一对应的。

在64位平台上，打印int下界:
int.c:4:17: warning: integer constant is so large that it is unsigned [enabled by default]
  printf("%d\n",-9223372036854775808);

C语言会将 -9223372036854775808 解释为符号运算符和9223372036854775808组成的表达式，而整数常量9223372036854775808已经超出了int型的取值范围。
所以C语言会将这个函数表示成一个long（64bit）型常量。
使用 printf("%ld",-9223372036854775808)可以解决这个问题。

再比如,
long i = 1234567890 * 1234567890 ;
会报错,因为int x int 的结果已经超出了int型常量可以表示的范围。
修正：
long i = 1234567890l * 1234567890;

# 浮点型
C标准 规定的浮点型有float, double, long double . 和整型一样，既没有规定每种类型占多少字节，也没有规定采用哪种表达形式。
浮点数的实现再各种平台上的实现差异很大，有的处理器有浮点数运算单元(Floating Point Unit, FPU),称为硬浮点(Hard-float)实现。
有的处理器没有浮点运算单元，只能做整数运算，需要用整数运算来模拟浮点运算，称为软浮点(Soft-float)运算。

大部分平台的浮点数实现遵循IEEE754规范，float型通常是32bit,double通常是64bit.

long double 型通常是比double型精度更高的类型，但各个平台的实现存在比较大的差异。
在x86平台上，大多数编译器实现的long double型是80位，因为x86的浮点运算单元具有80位精度，gcc实现的long double是12字节（96bit），
这是位了对齐到4字节边界。也有的编译器实现的long double型和double型精度相同，没有充分利用x86浮点运算单元的精度。
其他体系结构浮点运算单元的精度不同，编译器实现也会不同，例如PowerPC上的long double通常是128bit。

314e-2
3.14f 0.1L

## 类型转换

### Integer Promotion
凡是可以使用int 或者unsigned int 类型做右值的地方也都可以使用有符号或者无符号的char型，short型和Bit-field。如果原始类型的取值范围都能用int型表示，
则其类型被提升为int,如果原始类型的取值范围用int型表示不了，则提升为unsigned int型，这称为Integer Promostion。

C99规定 Integer Promotion适用于一下几种情况:
1. 如果一个函数的形参类型未知，例如使用了Old Style C风格的函数声明,或者函数列表中有...,那么调用函数时要对应相应的实参做Integer Promotion。
此外，相应的实参如果是float型的也要被提升为double型，这条规则称为Default Argument Promotion。
例如,printf的参数列表中有...，除了第一个形参之后，其他形参的类型都是未知的:
```
char ch = 'A'
printf("%c",ch);
```
ch 要被提升位int型之后再传给printf。

2. 算术运算中的类型转换。有符号或无符号的char型、short型和Bit-field再进行算术运算之前要先做Integer Promotion，然后才能参与计算。例如:
```
unsigned char c1 = 255, c2 = 2;
int n = c1 + c2;

### Usual Arithmetic Conversion
两个算术类型的操作数做算术运算，比如 a + b ，如果两边操作数的类型不同，编译器会自动做类型转换，是两边类型相同之后再做运算，这称为Usual
Arithmetic Conversion,转换规则如下：
1. 如果有一边的类型时long double, 则把另一边也转成 long double。
2. 如果有一边的类型是double, 则把另一边也转成double。
3. 如果有一边的类型是float，则把另一边也转成float。
4. 两边都是整型，首先按照上一节的规则对a和b进行Integer Promotion,如果类型仍不相同，则需要继续转换。我们规定char, short, int,long, long long 
的转换级别(Integer Conversion Rank) 一个比一个高，同一类型的有符号数和无符号数具有相同的Rank,转换规则如下:
- 如果两边都是有符号数，或者有无符号数，那么较低Rank的类型转换成较高Rank的类型。例如unsigned int 和 unsigned long做算术运算时都转成 unsigned long。
- 如果一边是无符号数另一边是有符号数，无符号数的Rank不低于有符号数的Rank,则吧有符号数转成另一边的无符号数类型。例如unsigned long  和 int 做算术
运算时都转成unsigned long, unsigned long和long做算术运算时也都转成unsigned long。
- 一边有符号另一边无符号，并且无符号数的Rank低于有符号数的Rank。这时又分为两种情况，如果有符号数类型能够覆盖无符号数类型的取值范围，则把无符号数
类型转成另一边的有符号类型。例如再遵循LP64的平台上unsigned int和long做算术运算时都转换成long。 否则，两边都转成有符号数的Rank对应的无符号类型。例如再遵循ILP32的平台上unsigned int和long做算术运算时都转成unsigned long。

到目前未知我们学过的+-*/%><>=<===!=运算符都需要做Usual Arithmetic Conversion,因为都要求两边操作数的类型一致。

### 由赋值产生的类型转换
如果赋值或者初始化时等号两边的类型不同，则编译器会把等号右边的类型转换成等号左边的类型再赋值。
```
int c = 3.14;
```
函数调用的传参和返回都满足这两种情况。

在函数调用和返回过程中发生的类型转换往往容易被忽视，因为函数原型和函数调用没有写在一起。
```
char c = getchar();
```
getchar的返回值时int型，这样赋值会引起类型转换，可能产生Bug。

### 强制类型转换
以上三种情况通称为 隐式类型转换(Implicit Conversion,或者Coercion),编译器一句他自己的一套规则将一种类型自动转换成另一种类型。
除此之外，程序员也可以通过类型转换运算符(Cast Operator)规定某个表达式要转换成何种类型，这称为显示类型转换(Explicit Conversion) 或者
强制类型转换(Type Cast)。
```
(double)3 + i
```
首先将整数3强制转换成double型(值为3.0),然后和整型变量i相加，适用于Usual Arithmetic Conversion原则，首先把i也转换成double型，然后两者相加，最后
整个表达式就是double型的。

### 编译器如何处理类型转换
M位类型 (值为X） -> N位的类型

