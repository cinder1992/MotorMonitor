#include "platform/my68k/error.h"
#include "stdio.h"
#include <stddef.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
	short status;
	int pc;
	short vector;
} errorFrame;

static const char* errorStrings[] = {
	"",
	"",
	"Access Violation",
	"Address error",
	"Illegal instruction",
	"Divide by zero",
	"CHK out of bounds",
	"TRAPV with overflow",
	"Privilege violation",
	"Trace",
	"Line 1010",
	"Line 1111",
	"RESERVED","RESERVED",
	"Format error",
	"Uninitialized Interrupt Vector",
	"RESERVED","RESERVED","RESERVED","RESERVED",
	"RESERVED","RESERVED","RESERVED","RESERVED",
	"Spurious Interrupt"
};

static const char* h = "0123456789ABCDEF";

void __attribute__((interrupt)) _err_bomb(void) {
	errorFrame* frame = __builtin_frame_address(0)+4;
	puts("\r\nBOMB exception, processor halted.\r\n");
	puts("Status: ");
	putc(h[(frame->status&0xF000)>>12]);
	putc(h[(frame->status&0x0F00)>>8]);
	putc(h[(frame->status&0x00F0)>>4]);
	putc(h[frame->status&0x000F]);
	puts(" Error: ");
	putc(h[(frame->vector&0xF000)>>12]);
	putc(h[(frame->vector&0x0F00)>>8]);
	putc(h[(frame->vector&0x00F0)>>4]);
	putc(h[frame->vector&0x000F]);
	putc(' ');
	puts(errorStrings[(frame->vector&0x00FF)>>2]);
	puts("\r\nPC: ");
	putc(h[(frame->pc&0xF0000000)>>28]);
	putc(h[(frame->pc&0x0F000000)>>24]);
	putc(h[(frame->pc&0x00F00000)>>20]);
	putc(h[(frame->pc&0x000F0000)>>16]);
	putc(h[(frame->pc&0x0000F000)>>12]);
	putc(h[(frame->pc&0x00000F00)>>8]);
	putc(h[(frame->pc&0x000000F0)>>4]);
	putc(h[frame->pc&0x0000000F]);
	halt: asm volatile("stop #0\n\t");
	goto halt;
}
