## 函数调用
在编译时加上-g选项，那么用objdump反汇编时可以把C代码和汇编代码穿插起来显示，这样C代码和汇编代码之间的对应关系可以看得更清楚。

gcc -S main.c 可以只生成汇编代码main.s，而不生成二进制的目标文件。