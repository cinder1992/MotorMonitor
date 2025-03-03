#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE* file, const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfprintf(file, format, vargs);
	va_end(vargs);
	return retv;
}
