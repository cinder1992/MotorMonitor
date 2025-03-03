#include <stdio.h>

int fputc(int chr, FILE* file) {
	switch((size_t)file) {
		case (size_t)stdout:
		case (size_t)stderr:
			return putchar((char) chr);
		default:
			return EOF;
	}
}

