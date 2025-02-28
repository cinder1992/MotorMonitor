#include <stdarg.h>
#include <stdio.h>

int fputc(int c, FILE* file) {
	switch((size_t)file) {
		case (size_t)stdout:
		case (size_t)stderr:
			return putchar((char) c);
		default:
			return EOF;
	}
}

int fputs(const char* str, FILE* file) {
	int i = 0;
	while(str[i] != '\0')
		if(fputc(str[i++], file) == EOF)
			return EOF;
	return i;
}

int puts(const char* str) {
	int rv1 = 0;
	int rv2 = 0;
	rv1 = fputs(str, stdout);
	if(rv1 == EOF)
		return EOF;
	rv2 = fputs("\r\n", stdout);
	if(rv2 == EOF)
		return EOF;
	return rv1 + rv2;
}

int fgetc(FILE* file) {
	switch((size_t)file) {
		case (size_t)stdin:
			return getchar();
		default:
			return EOF;
	}
}

static int __fputhex(FILE* file, int var) {
	int mask = 0xF0000000;
	const char* h = "123456789ABCDEF";
	int tmp;
	int rv = 0;
	while((var & mask) == 0) mask = mask >> 4;
	while(mask != 0) {
		tmp = fputc(h[var & mask], file);
		if(tmp == EOF) return EOF;
		rv += tmp;
		mask = mask >> 4;
	}
	return rv;
}

static int __parse_and_emit(FILE* file, const char* format, int* idx, va_list args) {
	int rv = 0;
	int tmp;
	switch(format[*idx]) {
		case '%':
			tmp = fputc('%', file);
			break;
		case 'c':
			tmp = fputc(va_arg(args, int), file);
			break;
		case 's':
			tmp = fputs(va_arg(args, char*), file);
			break;
		case 'x':
			tmp = __fputhex(file, va_arg(args, int));
			break;
		default:
			return EOF;
	}
	if(tmp == EOF) return EOF;
	rv += tmp;
	return rv;
}

int vfprintf(FILE* file, const char* format, va_list args) {
	int rv = 0;
	int i = 0;
	while(format[i] != '\0') {
		if(format[i] == '%') {
			i++;
			int temp = __parse_and_emit(file, format, &i, args);
			if(temp < 0)
				return temp;
			rv += temp;
		} else {
			int temp = fputc(format[i++], stdout);
			if(temp < 0)
				return temp;
			rv += temp;
		}
	}
	return rv;
}

int vprintf(const char* format, va_list args) {
	return vfprintf(stdout, format, args);
}

int fprintf(FILE* file, const char* format, ...) {
	int rv;
	va_list vargs;
	va_start(vargs, format);
	rv = vfprintf(file, format, vargs);
	va_end(vargs);
	return rv;
}

int printf(const char* format, ...) {
	int rv;
	va_list vargs;
	va_start(vargs, format);
	rv = vfprintf(stdout, format, vargs);
	va_end(vargs);
	return rv;
}
