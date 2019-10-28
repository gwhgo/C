1. '\0'
2. read only
3. char str[10] = "Hello"; <=> char str[10] = { 'H', 'e', 'l', 'l', 'o','\0'}
4. 可以不指定长度 char str[] = "Hello World.\n"
5. printf 回从数组str 的开头一直打印到Null字符为止，Null字符本身就是Non-printable字符，不打印。 如果数组str中没有Null字符，那么printf函数就会访问数组越界，后果可能会很诡异。
