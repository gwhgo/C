循环和递归是等价的。 
有些编程语言（如某些LISP实现）只有递归而没有循环。 
计算机指令能做的事情就是数据存取、运算、测试和分支、循环。 
Refer to : <Introduction to Automata Theory, Languages and Computation>

递归是计算机的精髓所在，也是编程语言的精髓所在。
几个例子：
1. 表达式 就是递归定义的
	表达式 -> 表达式(参数列表)
	参数列表 -> 表达式，表达式
2. 语句 也是递归定义的
	语句 -> if (控制表达式) 语句

可见编译器在解析我们编写的程序时一定也用了大量的递归，有关编译器的实现原理
Refer to < Compilers: Principles, Techniques & Tools>



