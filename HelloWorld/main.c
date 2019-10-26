#include <stdio.h>

/*
 *  comment1
 *  main: generate some simple output
 *
 */
void print()
{
	/*
	 *  first part : printf
	 */
	printf(/* comment2 */ "Hello, world.\n"); /* comment3 */
	/* costants & placeholders */
	/* c d f  in "%c , %d , %f " is a Conversion Specification */
	/* \n is a escape character 
	 * \n menas Line Feed
	 * \r means Carriage Return 
	 * \r \n is used in windows and HTTP for indicating jump to a new line
	 * \n is used in linux to do the same thing, and \r in linux could be displayed in the form of "^M"
	 * */
	/* escape chracter is processed during compliation */
	/* placeholder is processed when printf running */
	printf("character: %c\ninteger: %d\nfloating piont: %f\n",')',34,3.14);
}

void assignment()
{
	/* assignment here <=> declaration + definition */
	char firstletter;
	int id;
	int hour, minute;
	int hp;
	/* assignment again for intialation*/
	firstletter = 'g';
	id = 1;
	hour = 1;
	minute = 33;
	firstletter = 'g';
	id = 1;
	hour = 1;
	minute = 33;
	hp = 0;
	printf("namne : %c\n",firstletter);
	printf("id : %d\n",id);
	printf("login time: %d:%d\n",hour,minute);
	/* simple operator*/
	printf("login minutes: %d\n",hour*60 +  minute);
	/* ++ operator behind the operand */	
	/* 
	 * The result is 7.
	 * 1 + 2 + 3 = 6
	 * 2 + 2 + 3 = 7
	 */
	/*
	 * this will cause a failuer during compling
		printf("healing method 1! 诡术妖姬  ...the hp now : %d\n",++hp++);
	*/
	hp = 0;
	printf("healing method 1! 疾风剑豪  ...the hp now : %d\n",(++hp)+(++hp)+(++hp));
	hp = 0;
	printf("healing method 2! 时间刺客  ...the hp now: %d\n",hp+++hp+++hp++);
	/* char belong to Integer type */
	printf("%c -> after revolution: %c\n",firstletter,  firstletter + 1);
}
int main(void)
{	
	assignment();
	return 0;
}
