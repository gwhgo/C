# using man to check fucntion "printf"'s documents
man 3 printf

# 函数原型:
# int printf(const char *format,...);
# 第一个参数时 const char* 类型的，后面的...代表0个或者任意多个参数，这些参数的类型也是不确定的，这称为可变参数(Variable Argument)。

# 每个函数的原型都明确规定了返回值类型以及参数的类型和个数，即使像 printf 这样规定为不确定也是一种明确的规定，调用这些函数时要严格遵守这些规定，有时我们把函数叫作接口(interface), 调用函数就是使用这个接口，使用接口的前提是必须和接口保持一致。

# 关于 Man Page 
# Man Page 是 Linux开发最常用的参考手册，由很多页面组成，每个页面描述一个主题，这些主题被组织成若干个Section。
# FHS (Filesystem Hierarchy Standard) 规定了Man Page 各Section的含义， 如下:
# 1 用户命令  ls
# 2 系统调用 _exit
# 3 库函数 printf
# 4 特殊文件， null(4)描述了设备文件/dev/null和/dev/zero的作用，这个页面也叫zero.
# 5 系统配置文件的格式，例如passwd(5) 描述了系统配置文件/etc/passwd 的格式。
# 6 游戏
# 7 杂项，例如bash-builtins(7) 描述了bash的各种内建命令。
# 8 系统管理命令，例如ifconfig(8)

# 用户命令通常位于/bin和/usr/bin目录下。 
# 系统管理命令通常位于/sbin和/usr/sbin目录下。

# Man Page 存在重名现象，例如输入 man printf命令看到的并不是C函数printf,而是位于第一个section命令的printf。
# 可以输入 man -k printf 命令搜索那些页面的主题包含printf关键字。

