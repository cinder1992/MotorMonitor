.title "my68k: _start"
.cpu 68010

.section .text

.extern main, mfp_init, _init

.globl _start

_start:
	lea _USP, %a0
	movel %a0, %USP
	lea _lvectors, %a0
	lea _vectors, %a1
	movel #_vectors, %d0
	movel #_evectors, %d1
	subl %d0, %d1
0:
	move.b %a0@+, %a1@+
	dbra %d1, 0b
	lea _ldata, %a0
	lea _data, %a1
	movel #_data, %d0
	movel #_edata, %d1
	subl %d0, %d1
0:
	move.b %a0@+, %a1@+
	dbra %d1, 0b
	movel #_bss, %d0
	movel #_ebss, %d1
	subl %d0, %d1
	lea _bss, %a0
0:
	clr.b %a0@+
	dbra %d1, 0b
	andi #0xF8FF, %SR
	jsr _init
	jsr main
	/* main should never return, but if it does... */
	illegal

.end
