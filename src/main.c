#include <stdio.h>

void main() {
	const char str[] = "Hellorld!";
	puts(str);
	while(1) {
		putc(getc(stdin), stdout);
	}
}
