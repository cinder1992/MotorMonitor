#include "stdio.h"
#include "platform/my68k/mfp.h"

void putc(char c) { mfp_putc(c); }
char getc(void) { return mfp_getc(); }
void puts(const char* str) {
	int i = 0;
	while(str[i] != '\0') {
		putc(str[i++]);
	}
}
