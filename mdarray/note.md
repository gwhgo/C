1. C语言 -> row-major
2. Fortan -> Column-major
3. 嵌套Initializer
	int a[][2] = { {1,2},
				   {3,4},
				   {5,} };
	除了第一维的长度可以由编译器自动计算而不需要指定，其余各维都必须明确指定长度。
4. 利用C99的新特性 Memberwise Initialization
	int a[3][2] = { [0][1]  = 0, [2][1] = 8};

	struct complex_struct{
		double x,y;
	} a[4] = { [0].x = 8.0 };
	
	struct {
		double x,y;
		int count[4];
	} s = { .count[2] = 9};

		
数据驱动编程 (Data-dreiven Programming)
写代码最重要的是选择正确的数据结构来组织信息，设计控制流程和算法尚在其次，只要数据结构选择的正确，其他代码自然而然地就变得容易理解和维护了
Refer:
《人月神话》第九章	Show me your flowcharts and conceal your tables, and I shall continue to be mystified,. Show me your tables, and I won't usually need your flowcharts; they'll be obvious.
