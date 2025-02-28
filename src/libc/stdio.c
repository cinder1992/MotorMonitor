#include <stdarg.h>
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

int fputs(const char* str, FILE* file) {
	int idx = 0;
	while(str[idx] != '\0') {
		if(fputc(str[idx++], file) == EOF) {
			return EOF;
		}
	}
	return idx;
}

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

int fgetc(FILE* file) {
	switch((size_t)file) {
		case (size_t)stdin:
			return getchar();
		default:
			return EOF;
	}
}

static int fputhex(FILE* file, int var) {
	unsigned int mask = 0xF0000000;
	const char* hexstr = "123456789ABCDEF";
	int tmp;
	int retv = 0;
	while((var & mask) == 0) { mask = mask >> 4; }
	while(mask != 0) {
		tmp = fputc(hexstr[var & mask], file);
		if(tmp == EOF) { return EOF; }
		retv += tmp;
		mask = mask >> 4;
	}
	return retv;
}

static int parse_and_emit(FILE* file, const char* format, int* idx, va_list args) {
	int retv = 0;
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
			tmp = fputhex(file, va_arg(args, int));
			break;
		default:
			return EOF;
	}
	if(tmp == EOF) { return EOF; }
	retv += tmp;
	return retv;
}

int vfprintf(FILE* file, const char* format, va_list args) {
	int retv = 0;
	int idx = 0;
	while(format[idx] != '\0') {
		if(format[idx] == '%') {
			idx++;
			int temp = parse_and_emit(file, format, &idx, args);
			if(temp < 0) {
				return temp;
			}
			retv += temp;
		} else {
			int temp = fputc(format[idx++], stdout);
			if(temp < 0) {
				return temp;
			}
			retv += temp;
		}
	}
	return retv;
}

int vprintf(const char* format, va_list args) {
	return vfprintf(stdout, format, args);
}

int fprintf(FILE* file, const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfprintf(file, format, vargs);
	va_end(vargs);
	return retv;
}

int printf(const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfprintf(stdout, format, vargs);
	va_end(vargs);
	return retv;
}
