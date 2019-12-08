# Var Layout
我们在全局作用域和main函数的局部作用域定义了一些变量，并且引入了一些全新的关键字:
const static register 来修饰变量。
那么这些变量的存储空间如何分配呢？
我们可以在编译之后用readelf命令来查看他的符号表，了解各变量的地址分布，我们只截取关心的几行:
readelf -a a.out

64: 0000000000400600     4 OBJECT  GLOBAL DEFAULT   15 A
68: 0000000000601034     4 OBJECT  GLOBAL DEFAULT   24 a
42: 0000000000601038     4 OBJECT  LOCAL  DEFAULT   24 b
43: 000000000060103c     4 OBJECT  LOCAL  DEFAULT   24 a.2183
67: 0000000000601044     4 OBJECT  GLOBAL DEFAULT   25 c

## .rodata
变量A用const修饰，表示A是只读的，不可修改。 这个变量位于.rodata段。
 [15] .rodata           PROGBITS        00000000004005f0 0005f0 000024 00   A  0   0  8
.rodata section 在内存中的地址是0x4005f0 ~ 0x400614， 在文件中的地址是0x5f0~0x614.
我们使用hexdump来查看这个段的内容
```
000005f0  01 00 02 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000600  0a 00 00 00 48 65 6c 6c  6f 20 77 6f 72 6c 64 20  |....Hello world |
00000610  25 64 0a 00 01 1b 03 3b  30 00 00 00 05 00 00 00  |%d.....;0.......|
```
0a 00 00 00存放的就是变量A，同时我们还看到程序中的字符串字面值"Hello world %d\n"分配在.rodata段的末尾。字符串的值是只读的，这相当于在全局作用域定义了一个const数组:
```
const char helloworld[] = {'H','e','l','l'....}
```
在链接时，.rodata和.text段合并到Text Segment中，在加载运行时操作系统把Text Segment的页面只读保护起来，防止意外改写。从readelf的输出可以看出.rodata段和.text段被合并到一个Segment,.data和.bss段被合并到另一个Segment。
```
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .text .fini .rodata .eh_frame_hdr .eh_frame 
  03     .init_array .fini_array .jcr .dynamic .got .got.plt .data .bss 
```
像A这种const常量在定义时必须初始化。因为只有初始化时才有机会给他一个值，一旦定义之后就不能再改写了。如果给他赋值编译器会报错，也就是说，操作系统的内存管理和编译器的语义检查为全局const变量提供了双重保护。我们知道函数的局部变量在栈上分配，如果把局部变量声明为const就少了一层保护，操作系统无法对栈空间进行只读保护（因为栈上其他数据要求可写可读），但编译器仍可以做语义检查。

## .data
.data段中有三个变量：a b a.2183 
a 是一个全局符号，而b被关键字static修饰了，导致它称为一个局部符号，所以static在这里的作用时声明b为局部符号，如果把多个目标文件链接在一起，局部符号只能在某一个文件中定义和使用，而不能在一个目标文件中定义却在另一个目标文件中使用。因为链接器不会对局部符号做符号解析，一个函数定义前面也可以用static修饰，表示这个函数是局部符号。

还有一个a.1589是什么呢？ 他是main函数中的 static int a 
函数中的static变量不同于我们以前讲的局部变量，他并不是在调用函数时分配，在函数返回时释放，而是像全局变量一样静态分配，所以用"static"这个词。
另一方面，函数中的static变量也是局部作用域的，在别的函数中说变量a就不是他了，所以编译器给他的符号名加了一个后缀，a.2183，以便和全局变量以及其他函数的静态变量区分开。

.bss section 在内存中的地址是
[25] .bss              NOBITS          0000000000601040 001040 000008 00  WA  0   0  4
变量int c 也位于这个section中， .data 和 .bss 在链接时合并到Data Segment中，在加载运行时Data Segment的页面是可读可写的。 
.bss 和.data 的不同之处在于 .bss 在文件中不占用存储空间，加载到内存时这个段用0填充，C语言规定全局变量和static变量（不管是函数内的还是函数外的）如果不初始化则初值为0，未初始化和明确初始化为0的全局变量，static变量都会分配在.bss段。

现在还剩下main函数中的变量b和c没有分析。b是一个数组，在栈上分配。
我们看一下main函数的反汇编代码:
objdump -dS b.out

  char b[] = "Hello World";
  400536:       48 b8 48 65 6c 6c 6f    movabs $0x6f57206f6c6c6548,%rax
  40053d:       20 57 6f 
  400540:       48 89 45 e0             mov    %rax,-0x20(%rbp)
  400544:       c7 45 e8 72 6c 64 00    movl   $0x646c72,-0x18(%rbp)
        register int c = 50;
  40054b:       bb 32 00 00 00          mov    $0x32,%ebx

        printf("Hello world %d\n",c);
  400550:       89 de                   mov    %ebx,%esi
  400552:       bf 04 06 40 00          mov    $0x400604,%edi
  400557:       b8 00 00 00 00          mov    $0x0,%eax
  40055c:       e8 af fe ff ff          callq  400410 <printf@plt>

register int c 没有在栈上分配，而是直接存在%ebx寄存器中。这就是register关键字的作用。
在调用printf函数之前，将$0x400604 -> "Hello World %d\n"的首地址放入寄存器%edi中。

## Scope
作用域(Scope)概念适用于所有的标识符，而不仅仅是变量，C语言的作用域分为：

- 函数作用域(Function Scope) 在整个函数中都有效，只有标号属于函数作用域。
- 文件作用域(File Scope) 	标识符在函数外声明，从他声明开始的位置开始到源文件末尾都有效，严格来说应该是知道编译单元(Translation Unit) 末尾都有效。 比如源文件 a.c 包含了 b.h 和 c.h，那么经过预处理把b.h 和  c.h 在a.c中展开之后得到的代码称为一个编译单元。编译器把每个编译单元分别编译成一个目标文件，最后链接器把这些目标文件链接到一起成为一个可执行文件。
  上例中函数外的A,a,b,c 以及标识符main都是File Scope。

- 块作用域(Block Scope)  
	main函数里的 a,b,c 还有函数的形参都是块作用域的。

- 函数原型作用域(Function prototype Scope)
	int foo(int a, int b)
	int foo(int, int)

对于属于同一命名空间(Name Space)的重名标识符，内层作用域的标识符将覆盖外层作用域的标识符。 
命名空间分为以下几类:
- 语句标号 
- struct, enum 和 union的Tag
- struct 和 union的成员名
- 所有其他标识符 
	例如变量名、函数名、宏定义、typedef定义的类型名、enum成员
- 如果宏定义和其他标识符重名，则宏定义覆盖所有其他标识符，因为宏定义在预处理阶段先处理，而其他标识符在编译阶段处理。

标识符的链接属性 (Linkage):
- 外部链接(External Linkage) 一个标识符在不同的编译单元中可能被声明多次，当这些编译单元链接成一个可执行文件时，如果这些声明都代表同一个变量或者函数（即代表同一个内存地址），则这个标识符具有External Linkage。 具有External Linkage的标识符编译后在目标文件中是全局符号。上例函数外声明的a,c以及main和printf都具有External Linkage.
- 内部链接(Internal Linkage) 函数外声明的b具有Internal Linkage.
	main函数内部的static int a不算
- 无链接属性(No Linkage) 除以上情况都属于No Linkage,例如函数的局部变量，以及不表示变量和函数的其他标识符。

具有External Linkage的标识符如何在多个编译单元中多次声明？

具有Internal Linkage的标识符如何在一个编译单元中重复声明？

存储类修饰符 (Storage Class Specifier) , 可以修饰变量或函数声明。

- static 静态分配 ， 用static修饰的文件作用域的变量或函数具有Internal Linkage.
- auto  用它修饰的变量在函数调用时自动在栈上分配存储空间，函数返回时自动释放。main中的b实际上就是auto修饰的，但可以省略不写，auto不能用于修饰文件作用域的变量。
- register 不能修饰文件作用域变量。 如果无法分配寄存器 ， -> auto。 
- extern  多次声明一个具有External Linkage或Internal Linkage的标识符.
- typedef ...
> Const 实际上不是Storage Class Specifier 而是 Type Qualiifer,和volatile,restric一样

## 修饰顺序
Storage Class Specifier  | Function Specifier | Type Qualifier | Type Specifier


## 生存期 (Storage Duration, Lifetime)
- 静态生存期 (Static Storage Duration)
	External Linkage, Internal Linkage 或者被static修饰的变量，在程序开始执行时分配内存才能和初始化,此后便一直存在直到程序结束.这种变量通常位于.rodat, .data, .bss段。 
- 自动生存期(Automatic Storage Duration)
	无连接属性并且没有被static修饰的变量，这种变量在块作用域时在栈上或者寄存器中分配，在退出块作用域时释放.
- 动态分配生存期(Allocated Storage Duration)
	malloc fre 堆






