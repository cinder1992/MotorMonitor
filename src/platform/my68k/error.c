#include "platform/my68k/error.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

void (*userErrorHandlers[16])(void);

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

void __attribute__((interrupt)) err_bomb(void) {
	errorFrame* frame = __builtin_frame_address(0)+4;
	puts("\r\nBOMB exception, processor halted.\r\n");
	printf("Status: %x ", frame->status);
	printf("Error: %x\r\n ", frame->vector);
	puts(errorStrings[(frame->vector&0x00FF)>>2]);
	printf("PC: %x", frame->pc);
	halt: asm volatile("stop #0\n\t");
	goto halt;
}
