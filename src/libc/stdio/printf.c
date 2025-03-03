#include <stdio.h>
#include <stdarg.h>

int printf(const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfprintf(stdout, format, vargs);
	va_end(vargs);
	return retv;
}
