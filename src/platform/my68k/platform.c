#include <stdio.h>
#include "platform/my68k/mfp.h"

int putchar(int chr) { mfp_putc((unsigned char)chr); return chr; }
int getchar(void) { return (int)mfp_getc(); }

