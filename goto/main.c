/*
 * 滥用goto语句会使程序的控制流程非常复杂，可读性很差。
 * goto语句不是必须存在的，显然可以用别的办法替代
 * 一般来说goto用来处理错误，C++中由Exception处理的语法来替代。
 */

for(...)
	for(...)
	{
		if (错误)
			goto error;
	}
	error:
		错误处理;

