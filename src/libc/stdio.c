#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

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

static void fgethex(FILE* __restrict file, int* var) {
	*var = 0;
	int val;
	do {
		val = toupper(fgetc(file));
		switch(val) {
			case '0' ... '9':
				*var = (*var << 4) | (val - '0');
				break;
			case 'A' ... 'F':
				*var = (*var << 4) | ((val - 'A')+'\x0A');
			default:
				break;
		}
	} while(isxdigit(val));
}

static void fgetdec(FILE* __restrict file, int* var){
	*var = 0;
	int val;
	do {
		val = fgetc(file);
		if(isdigit(val)) {
			*var = (*var * '\x0A') + (val - '0');
		} else {
			break;
		}
	} while(isdigit(val));
}

static void fgets(FILE* __restrict file, char* str, int len) {
	int idx = 0;
	int val;
	for(int i = 0; i < len; i++) {
		val = fgetc(file);
		if(isgraph(val)){
			str[idx] = (char)val;
			idx++;
		} else {
			str[idx] = '\0';
			break;
		}
	}
	str[idx] = '\0';
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

static inline void getlenvar(const char* format, int* idx, int* val) {
	*val = 0;
	while(isdigit(format[*idx])) {
		*val = (*val * '\x0A') + (format[*idx++] - '0');
	}
}


int vfscanf(FILE* file, const char* format, va_list args) {
	int retv = 0;
	int idx = 0;
	int tmp;
	while(format[idx] != '\0') {
		while(isspace(format[idx]) && format[idx] != '\0') { idx++; } //skip whitespace
		if(format[idx] != '\0') {break;} //dumb guard
		if(format[idx] != '%') {
			if(format[idx] != fgetc(file)) {
				return retv;
			}
		} else { //format[idx] == '%'
			switch(format[++idx]) {
				case 'x':
				case 'X':
					fgethex(file, va_arg(args, int*));
					retv++;
					break;
				case 'd':
					fgetdec(file, va_arg(args, int*));
					retv++;
					break;
				case 's':
					tmp = !0;
					if(isdigit(format[idx + 1])) {
						idx++;
						getlenvar(format, &idx, &tmp); //length
					}
					fgets(file, va_arg(args, char*), tmp);
					retv++;
					break;
				default:
					return retv;
					break;
			}
		}
	idx++;
	}
	return retv;
}

int vscanf(const char* format, va_list args) {
	return vfscanf(stdin, format, args);
}

int fscanf(FILE* file, const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfscanf(file, format, vargs);
	va_end(vargs);
	return retv;
}

int scanf(const char* format, ...) {
	int retv;
	va_list vargs;
	va_start(vargs, format);
	retv = vfscanf(stdin, format, vargs);
	va_end(vargs);
	return retv;
}
