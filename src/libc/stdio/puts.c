#include <stdio.h>

int puts(const char* str) {
	int rv1 = 0;
	int rv2 = 0;
	rv1 = fputs(str, stdout);
	if(rv1 == EOF) {
		return EOF;
	}
	rv2 = fputs("\r\n", stdout);
	if(rv2 == EOF) {
		return EOF;
	}
	return rv1 + rv2;
}
