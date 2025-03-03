#include <stdio.h>
#include <stdarg.h>

int fscanf(FILE* file, const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfscanf(file, format, vargs);
	va_end(vargs);
	return retv;
}
