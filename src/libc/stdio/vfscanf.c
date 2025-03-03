#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

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
		if(format[idx] == '\0') {break;} //dumb guard
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
					fgets(va_arg(args, char*), tmp, file);
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
