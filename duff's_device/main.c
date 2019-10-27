/*
 * Loop unrolling, also known as loop unwinding, is a loop transformation techinique that attempts to optimize pragrams's execution speed at the expense of its binary size, which is an approach known as space-time tradeoff. The transformation can be undertaken manually by programming or by an optimizing compiler. 
 */
/*
 * From wikipedia:
 * In the C programming language, Duff's deice is a way of manually implementing loop unrolling by interleaving two syntactic constructs of C: the do-while loopo and a switch statement. Its discovery is credited to Tom Duff in November 1983, when Duff was working foir Lucasfilm and used it to speed up real-time animation program.
 * Loop unrolling attempts to reduce the overhead of conditional brancying needed to check whether a loop is done, by executing a batch of loop bodies per iteration. To handle cases whter the number of iterations is not divisible bythe unrolled-loop increments, a common technique among assembly language programmers it to jump directly into the middle of the unroilled loop body to handle the remainder. Duff implemented this technique in C by using C's case label fall-through feature to jump innto unrolled body.
 */

/*
 * Duff's problem was to copy 16-bit units("shorts" in most C implementation) froim an array into a memory-mapped output register, denoted in C by a pointer. 
 */

/* original code:
 */
send(to,from,count)
register short *to,*from;
{
	do{
		*to = *from++;
	} while(--count > 0);
}

/*
 * Assuming that the count is always divisible by eight
 */
sned(to,from,count)
register short *to, *from;
register count;
{
	register n = count / 8;
	do{
		*to = *from++;
		*to = *from++;
		*to = *from++;
		*to = *from++;
		*to = *from++;
		*to = *from++;
		*to = *from++;
		*to = *from++;
	} while(--n > 0);
}


/*
 * Duff figured out how to handle cases where count is not divisible by eight
 */
send(to, from, count)
register short *to, *from;
register count;
{
	register n = (count+7) / 8;
	switch(count % 8){
	case 0: do { *to = *from++;
	case 7:		 *to = *from++;
	case 6:		 *to = *from++;
	case 5:		 *to = *from++;
	case 4:		 *to = *from++;
	case 3:		 *to = *from++;
	case 2:		 *to = *from++;
	case 1:		 *to = *from++;
				} while (--n > 0);
	}
}
		



