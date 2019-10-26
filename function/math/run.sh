# 
gcc -lm main.c -o main 2> error.log
if [ $? == 0 ];then
	./main
else
	echo "编译失败, 查看 error.log"	
fi

