#include <stdio.h>

int putchar(int chr) {
	unsigned char newchr = (unsigned char)chr;
	asm volatile(
		"movq $1, %%rax\n\t"
		"movq %0, %%rsi\n\t"
		"movq %%rax, %%rdi\n\t"
		"movq $1, %%rdx\n\t"
		"syscall\n\t"
		"movq $74, %%rax\n\t"
		"movq $1, %%rdi\n\t"
		"syscall\n\t"
		: //no outputs
		: "r" (&newchr)
		: "%rax", "%rsi", "%rdi", "%rdx", "memory"
	);
	return chr;
}
int getchar(void) {
	char retv = 0;
	asm volatile(
		"movq $0, %%rax\n\t"
		"movq %0, %%rsi\n\t"
		"movq $1, %%rdi\n\t"
		"movq $1, %%rdx\n\t"
		"syscall\n\t"
		: //no outputs
		: "r" (&retv)
		: "%rax", "%rsi", "%rdi", "%rdx", "memory"
	);
	return (int)retv;
}
