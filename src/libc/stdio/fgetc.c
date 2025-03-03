#include <stdio.h>

int fgetc(FILE* file) {
	switch((size_t)file) {
		case (size_t)stdin:
			return getchar();
		default:
			return EOF;
	}
}
