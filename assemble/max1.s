.section .data
data_items:
	 .long 1,2,3,4,4,3,2,1,0

.section .text
.globl _start
_start:
	movl $0,%edi
	movl data_items(,%edi,4),%ebx
	cmpl $0, %ebx
	je loop_exit

loop_start:
	incl %edi
	movl data_items(,%edi,4),%eax
	cmpl $0, %eax
	je loop_exit
	cmpl %ebx, %eax
	jle loop_start
	movl %eax,%ebx
	jmp loop_start

loop_exit:
	movl $1,%eax
	int $0x80
	
