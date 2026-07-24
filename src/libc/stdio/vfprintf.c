#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* K&R String Reverse */
static inline void reverse(char s[]) {
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* Modified K&R itoa */
static int utoa(unsigned int n, int base, char* s) {
	int i;
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = base <= 10 || n % base < 10 ? n % base + '0' : n % base + ('A' - 0xA);   /* get next digit */
	} while ((n /= base) > 0);     /* delete it */
	s[i--] = '\0';
	reverse(s);
	return i; //return index of last non-null character
}

/* Modified K&R itoa */
static int itoa(int n, int base, char* s) {
	int i, sign = 0;
	if(n < 0) sign = 1;
	i = utoa(sign ? -n : n,base,sign ? s + 1 : s); //UGLY HACK
	if(sign) {
		s[0] = '-';
		i++;
	}
	return i;
}

int vfprintf(FILE* file, const char* format, va_list args) {
	int retv = 0;
	int idx = 0;
	while(format[idx] != '\0') {
		if(format[idx] == '%') {
			idx++;
			int temp;
			char s[32+2];
			switch(format[idx]) {
				case '%':
					temp = fputc('%', file);
					break;
				case 'c':
					temp = fputc(va_arg(args, int), file);
					break;
				case 's':
					temp = fputs(va_arg(args, char*), file);
					break;
				case 'x':
					itoa(va_arg(args, int), 16, s);
					temp = fputs(s, file);
					break;
				case 'd':
					itoa(va_arg(args, int), 10, s);
					temp = fputs(s, file);
					break;
				default:
					return EOF;
			}
			idx += 1;
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
