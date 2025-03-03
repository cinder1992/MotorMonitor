#include <stdio.h>

int fputs(const char* str, FILE* file) {
	int idx = 0;
	while(str[idx] != '\0') {
		if(fputc(str[idx++], file) == EOF) {
			return EOF;
		}
	}
	return idx;
}
