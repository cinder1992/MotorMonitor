.title "my68k: _start"
.cpu 68010

.section .text

.extern main, mfp_init

.globl _start

_start:
	lea _USP, %a0
	movel %a0, %USP
	lea _ldata, %a0
	lea _data, %a1
	movel _data, %d0
	movel _data, %d1
	subl %d0, %d1
again:
	move.b %a0@+, %a1@+
	dbra %d1, again
	movel _bend, %d0
	movel _bstart, %d0
	subl %d0, %d1
	movel _bstart, %a0
again2:
	clr.b %a0@+
	dbra %d0, again2
	andi #0xF8FF, %SR
	jsr mfp_init
	jmp main

.end
