#include <stdio.h>
#include <stdarg.h>

int scanf(const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfscanf(stdin, format, vargs);
	va_end(vargs);
	return retv;
}
