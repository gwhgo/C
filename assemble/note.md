# 汇编
汇编中以.开头的名称并不是指令的助记符，而是给汇编器的一些特殊指示，被称为汇编指示(Assembler Directive)或者伪操作(Pseudo-operation)mbler Directive)或者伪操作(Pseudo-operation)。
.section 指示把代码划分成若干段(Section),程序被操作系统家在执行时，每个段没加载到不同的地址，操作系统对不同的页面设置不同的读、写、执行权限
	.data 段保存程序的数据，是可读可写的，相当于C程序的全局变量。
	.text 段保存代码，是可读可执行的。
		.global _start _start是一个符号(Symbol),符号在汇编中代表一个地址，可以用在指令中，汇编程序经过汇编器的处理之后，所有符号都被替换成它所代表的地址值。
					   	.globalg告诉汇编器，_start这个符号链接器要用到，所以要再目标文件的符号表中标记他是一个全局符号。_start就像C程序的main函数一样特殊，把他设置成整个函数的入口地址。

指令：
	movl $4,%ebx 这条指令要求CPU内部产生一个数字1，并保存到eax寄存器种。mov的后缀l表示long，说明是32bit的传送指令。这条指令不要求CPU读内存，1这个数是在CPU内部产生的，称为立即数(Immediate)。
				 在汇编程序中，立即数前面要加$, 寄存器名前要加%， 以便跟符号名区分开。
	int $0x80    1. int指令称为软中断指令，可以用这条指令故意产生一个异常，异常的处理和中断类似，CPU从用户模式切换到特权模式，然后跳转到内核代码执行异常处理程序。
				 2. int指令种的立即数0x80是一个参数，在异常处理程序中要根据这个参数决定如何处理，在Linux内核中int $0x80这种异常称为系统调用(System Call)。内核提供了很多系统服务供用户程序使用，
					但这些系统服务不能像库函数（比如printf)那样调用，因为执行用户程序时CPU处于用户模式，不能直接调用内核函数，所以需要通过系统调用切换CPU模式，经由异常处理程序进入内核，用户
					程序只能通过寄存器传几个参数，之后就要按照内核设计好的代码路线走，而不能任由用户程序随心所欲地调用内核函数，这样可以保证系统服务可以安全地被调用。在调用结束之后，CPU再切回用户模式，
					继续执行int 0x80的下一条指令，在用户程序看来就像是函数调用和返回一样。
	eax 和 ebx是传递给系统调用的两个参数。eax的值: 系统调用号（_exit的系统调用好是1)。 ebx的值是传给_exit的参数，表示退出状态。大多数系统调用完成之后会返回用户空间继续执行后面的指令，而_exit系统调用比较
	特殊，它会终止当前进程。


x86寄存器
General-Purpose : eax, ebx, ecx, edx, edi, esi

Special : 
	ebp,esp : 维护函数调用的栈帧
	eip     : 程序计数器
	eflags	: 计算中产生的标志位 -- 进位标志、溢出标志、零标志、负数标志


## 寻址方式
访问内存时在指令中可以用多种方式表示内存地址，比如：数组基地址、元素长度、下标 三个量，增加了寻址的灵活性。

ADDRESS_OR_OFFSET(%BASE_OR_OFFSET,%INDEX,MULTIPLIER)

FINAL_ADDRESS = ADDRESS_OR_OFFSET + BASE_OR_OFFSET + MULTIPLIERxINDEX

ADDRESS_OR_OFFSET和MULTIPLIER必须是常数，BASE_OR_OFFSET和INDEX必须是寄存器。

- 直接寻址(Direct Addressing Mode) movl ADDRESS, %eax 把ADDRESS地址处的32位数传送到eax寄存器
- 变址寻址 (Indexed Addressing Mode)	movl data_items(,%edi,4),%eax就属于这种寻址方式。用于访问数组元素比较方便 
- 基址寻址 (Base Pointer Addressing Mode)movl 4(%eax),%eax 访问结构体成员比较方便
- 立即数寻址(Immediate Mode) movl $12, %eax
- 寄存器寻址 (Register Addressing Mode)movl $12,%eax


## ELF文件
ELF文件格式是一个开放标准，各种UNIX系统的可执行文件都采用ELF格式，它有以下三种类型：
- 可重定位的目标文件 (Relocatable 或者 Object File)
- 可执行文件 (Executable)
- 共享库(Shared Object, 或者Shared Library)
程序 汇编、链接、运行过程:
1. max.s
2. assembler(max.s) -> max.o 目标文件由若干个Section组成。除了我们自己编写section, 汇编器还会自动添加一些Section(比如符号表).
3. linker(max.o,...) -> 把目标文件中的Section合并成几个Segment,生成可执行文件max.
4. Loader(max) -> 根据可执行文件中的Segment信息加载运行这个程序。

一个Segment由一个或者多个Section组成，这些Section加载到内存时具有相同的访问权限。
有些Section只对连接器有意义，在运行时用不到，也不需要加载到内存，那么就不属于任何Segment。

## 目标文件
`
readelf -a -W max.o
`
文件地址的定义: 开头是0，然后一个字节占用一个地址。
Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        0000000000000000 000040 00002d 00  AX  0   0  1
  [ 2] .rela.text        RELA            0000000000000000 000178 000030 18   I  5   1  8
  [ 3] .data             PROGBITS        0000000000000000 00006d 00001c 00  WA  0   0  1
  [ 4] .bss              NOBITS          0000000000000000 000089 000000 00  WA  0   0  1
  [ 5] .symtab           SYMTAB          0000000000000000 000090 0000c0 18      6   7  8
  [ 6] .strtab           STRTAB          0000000000000000 000150 000028 00      0   0  1
  [ 7] .shstrtab         STRTAB          0000000000000000 0001a8 000031 00      0   0  1

Addr列指出这些Section加载到内存中的地址(虚拟地址), 目标文件中各Section中的加载地址是待定的，所以是0...0，到链接时再确定这些地址。
Off和Size列指出各Section的起始文件地址和长度。

文件布局:
0		ELF Header
0x40	.text
0x6d	.data
0x89	.bss
0x90	.symtab 
0x150	.strtab
0x178	.rela.text
0x1a8	.shstrtab
0x1e0	Section Header

`
hexdump -C max.o
`

.shstrtab 保存着各Section的名字，.strtab段保存着程序中用到的符号的名字，每个名字都是以Null结尾的字符串。

.bss 段保存着全局变量(0初始化）。

.rel.text 告诉链接器指令中的那些地方需要做重定位。

.symtab 时符号表。 Ndx列是每个符号所在的Section编号. Value列是每个符号所代表的地址，在目标文件中，符号地址都是相对于该符号所在Section的相对地址。 Bind列指明了符号时Global还是Local。

反汇编：
```
objdump -d max.o
```
目前所有指令用到的符号地址都是相对地址，data_items的地址直接是0，下一步链接器要修改这些指令，把其实的地址都改成加载时用到的内存地址，这些指令才能正确执行。

## 可执行文件

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        00000000004000b0 0000b0 000030 00  AX  0   0  1
  [ 2] .data             PROGBITS        00000000006000e0 0000e0 000024 00  WA  0   0  1
  [ 3] .symtab           SYMTAB          0000000000000000 000108 000108 18      4   7  8
  [ 4] .strtab           STRTAB          0000000000000000 000210 000040 00      0   0  1
  [ 5] .shstrtab         STRTAB          0000000000000000 000250 000027 00      0   0  1

Type改成了EXEC。
Entry point address改成了0x4000b0。
.rel.text 昨晚链接就没用了，所以也被删掉。


.text段的地址被改成了0x4000b0, .data段的地址被改成了6000e0。


Program Headers:
  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align
  LOAD           0x000000 0x0000000000400000 0x0000000000400000 0x0000e0 0x0000e0 R E 0x200000
  LOAD           0x0000e0 0x00000000006000e0 0x00000000006000e0 0x000024 0x000024 RW  0x200000
多出来的Program Header Table描述了两个Segment的信息。

.text段和ELF Header, Program Header Table一起组成了一个Segment (FileSize 0xe0) -> Text Segment
.data段组成了另一个Segment(FileSize 0x24)

VirtAddr列指出了加载的虚拟地址，在x86平台上，PhysAddr列是没有意义的。
Align代表了平台(x86,x64)对应的内存页面的大小，这里是512 * 4KB。
在加载文件中也要分成若干页，文件中的一页对应内存中的一页。

这个可执行文件很小，总共也不超过一页，但是两个Segment必须加载到两个不同的页面，因为MMU的权限保护机制以页为单位，一个页面只能设置一种权限。

为了简化链接器和加载器的实现，还规定了每个Segment在页面中偏移多少加载到内存页面中也要偏移多少。

原来目标文件符号表中的Value都是相对地址，现在都改成绝对地址了。
此外，还添加了三个符号 "__bss_start, _edata, _end"  __"
这些符号在链接脚本中定义，被链接器添加到可执行文件中。

```
objdump -d max
```

指令中的相对地址都改成绝对地址了。data_items就得到了修改，是根据 目标文件中.rel.text段提供了重定位信息得到修改的: 第一列Offset的值就是.text段需要修改的地方.

用strip去除可执行文件的符号信息，可以有效减少文件的尺寸而不影响运行。
不要对目标文件和共享库使用strip命令，因为链接器需要利用目标文件和共享库中的符号信息来做链接。

