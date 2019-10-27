gcc main.c -o main
if [ $? == 0 ];then
	./main
else
	echo "编译错误"
fi
