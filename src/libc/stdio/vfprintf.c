#include <stdio.h>
#include <stdarg.h>

static int fputhex(FILE* file, int var) {
	unsigned int mask = 0xF0000000;
	const char* hexstr = "0123456789ABCDEF";
	int tmp;
	int retv = 0;
	while(((var & mask) == 0) && mask != 0) { mask = mask >> 4; }
	while(mask != 0) {
		tmp = fputc(hexstr[var & mask], file);
		if(tmp == EOF) { return EOF; }
		retv += tmp;
		mask = mask >> 4;
	}
	return retv;
}

static inline int parse_and_emit(FILE* file, const char* format, int* idx, va_list args) {
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
	*idx += 1;
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
