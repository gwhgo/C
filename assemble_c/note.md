## 函数调用
在编译时加上-g选项，那么用objdump反汇编时可以把C代码和汇编代码穿插起来显示，这样C代码和汇编代码之间的对应关系可以看得更清楚。

gcc -S main.c 可以只生成汇编代码main.s，而不生成二进制的目标文件。

3       int bar(int c,int d)
4       {
5               int e = c + d;
6               return e;
7       }

(gdb) disassemble 
Dump of assembler code for function bar:
   0x00000000004004cd <+0>:     push   %rbp
   0x00000000004004ce <+1>:     mov    %rsp,%rbp
   0x00000000004004d1 <+4>:     mov    %edi,-0x14(%rbp)
   0x00000000004004d4 <+7>:     mov    %esi,-0x18(%rbp)
=> 0x00000000004004d7 <+10>:    mov    -0x18(%rbp),%eax
   0x00000000004004da <+13>:    mov    -0x14(%rbp),%edx
   0x00000000004004dd <+16>:    add    %edx,%eax
   0x00000000004004df <+18>:    mov    %eax,-0x4(%rbp)
   0x00000000004004e2 <+21>:    mov    -0x4(%rbp),%eax
   0x00000000004004e5 <+24>:    pop    %rbp
   0x00000000004004e6 <+25>:    retq 

(gdb) p $rbp
$1 = (void * ) 0x7fffffffe328

(gdb) p $rsp
$2 = (void * ) 0x7fffffffe328
(gdb) x/20 $rsp
0x7fffffffe328: -7360   32767   4195588 0
0x7fffffffe338: 3       2       -7344   32767
0x7fffffffe348: 4195609 0       0       0
0x7fffffffe358: -140311403      32767   0       32
0x7fffffffe368: -7112   32767   0       1

在执行程序时，操作系统会为进程分配一块栈空间来保存函数帧，esp(rsp)寄存器总是指向栈顶。
在x86平台上这个栈的地址是由高地址向低地址增长的，每次调用一个函数都要分配一个栈帧来保存参数和局部变量。

注意函数调用和返回过程中的这些规则：
- 参数压栈传递，并且是从右向左依次压栈
- ebp总是指向当前栈帧的栈底,在vm05虚拟机上，寄存器是ebp
- 返回值是通过eax寄存器进行传递 , 在vm05虚拟机上，寄存器是eax
这些规则并不是体系结构所强加的，ebp寄存器并不是必须这么用的，函数的参数和返回值也并不是一定要这么传，只是操作系统和编译器规定了以这样的方式实现C代码中的函数调用，这称为Calling Convention.


# 为什么汇编程序的入口是"_start" 而C程序的入口是main后函数呢？
理解gcc的编译步骤:
gcc -S 				main.c -> main.s
gcc -c 				main.c|main.s -> main.o
gcc 				main.c|main.s|main.o -> main


即使 gcc main.c -o main命令一步完成编译，gcc内部还是要分三部分来，用-v选项可以了解详细的编译过程。
gcc只是一个外壳而不是真正的编译器，真正的C编译器是 /usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1, gcc调用C编译器、汇编器和链接器完成C代码的编译工作。
i/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/collect2 是ld的外壳，它调用ld完成工作。
具体过程如下：
1. fun.c 被编译器编译成汇编程序 /tcmp/ccVQVmUb.s
 /usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1 -quiet -v fun.c -quiet -dumpbase fun.c -mtune=generic -march=x86-64 -auxbase fun -version -o /tmp/ccVQVmUb.s
2.汇编程序被as链接成目标文件
  as -v --64 -o /tmp/ccscVCMl.o /tmp/ccVQVmUb.s 
3. 这个目标文件连同几个目标文件 (crt1.o, crti.o, crtbegin.o, crtend.o, crtn.o) 一起链接成可执行文件main。 在链接过程中还用-l选项指定了一些库文件，有libc,libgcc,libgcc_s等。有些库是共享库，需要动态链接，所以用-dynamic-linker选项指定动态链接器是/lib64/ld-linux-x86-64.so.2 。 
/usr/libexec/gcc/x85_64-redhat-linux/4.8.5/collect2 --build-id --no-add-needed --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o main /usr/lib/gcc/x86_64-redhat-li    nux/4.8.5/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtbegin.o -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x8    6_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccscVCMl.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed     -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-redhat-linux/4.8.5/crtend.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o


我们使用nm工具分析crt1.o 中的符号:
"
vm05:root 69 1059 /usr/lib64-->nm crt1.o 
0000000000000000 D __data_start
0000000000000000 W data_start
0000000000000000 R _IO_stdin_used
                 U __libc_csu_fini
                 U __libc_csu_init
                 U __libc_start_main
                 U main
0000000000000000 T _start
"_useless line

U main 这一行表示main这个符号在ctr1.o中被引用，但是没有定义(Undefined),因此需要别的目标文件提供一个定义并且和crt1.o链接在一起。
T _start 这个符号表示_start这个符号在crt1.o中提供了定义，这个符号的类型是代码(Text).

C程序的入口点其实是crt1.o提供的_start, 它首先做一些初始化工作（以下称为启动例程，Startup Routine).
_useless line
然后调用我们编写的main函数，所以_start才是真正的入口点。而main函数是被_start函数调用的。

