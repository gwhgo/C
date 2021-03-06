# 使用math.h生命的库函数, gcc 需要添加 -lm选项， 因为数学函数位于libm.so库文件中。这些库文件通常位于/lib目录下。
# 我们一般用到的库函数通常位于libc.so中(比如printf)， 使用libc.so gcc 不需要填加 -lc 选项，因为gcc 默认会添加.
gcc -lm main.c -o main 2> error.log
if [ $? == 0 ];then
	./main
else
	echo "编译失败, 查看 error.log"	
fi


# 关于C标准库
# C标准主要由两部分组成: 1. 描述C的语法 2.描述C标准库
# C标准库 定义了一组标准头文件，每个头文件中包含一些相关的函数、变量、类型声明和宏定义。
# 要在一平台上支持C语言，不仅要实现C编译，还要实现C标准库， 这样的实现才符合C标准。 
# 当然， 不符合C标准的实现也是存在的， 例如很多单片机的C语言开发工具就只有C编译器而没有完整的C标准库。 

# Linux平台上使用最广泛的C函数库是glibc, 其中包括C标准库的实现，也包括C标准库的实现，也包括C标准之外的各种系统函数。
# 几乎所有的C程序都需要调用glibc的库函数，所以glibc是Linux平台C程序运行的基础。
# glibc提供一组头文件和一组库文件， 最基本、最常用的C标准库函数和系统函数都在libc.so库文件中。 
# 几乎所有C程序的运行都依赖于libc.so ，也有些进行数学计算的C程序除了libc.so之外还依赖于libm.so，也有很多C程序依赖于其他库文件。

# glibc 并不是Linux平台唯一的基础C函数库，也有人在开发别的C函数库，比如适用于嵌入系统的uClibc。


