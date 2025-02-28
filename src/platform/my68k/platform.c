#include <stdio.h>
#include "platform/my68k/mfp.h"

int putchar(int chr) { mfp_putc(((unsigned char)chr&255)); return 0; }
int getchar(void) { return (int)mfp_getc(); }

