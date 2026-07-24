MEMORY
{
    VECTBL (rw) : ORIGIN = 0, LENGTH = 0x400
    RAM (rwx) : ORIGIN = 0x400, LENGTH = 1M - 0x400
    ROM (rx) : ORIGIN = 0xe00000, LENGTH = 1M
}

SECTIONS
{
	ENTRY(_start)

	/* Vector table */
	.vectors : {*(.vectors)} >VECTBL AT>ROM

	/* ROM entries */
	.text : { *(.text) *(.text*) } >ROM
	.rodata : { *(.rodata) *(.rodata*) } >ROM
	/*.ctors and .dtors are both in ROM*/
	.ctors ALIGN(4) : {
		KEEP (*crtbegin.o(.ctors))
		KEEP (*crtbegin?.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
	} >ROM
	.dtors ALIGN(4) : {
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
	} >ROM
	
	/* RAM entries */
	.tpa ORIGIN(RAM) (NOLOAD) : { . = ABSOLUTE(ORIGIN(RAM) + LENGTH(RAM) - (8K + 1024)); _etpa = .; } >RAM
	.ustack (NOLOAD) : { . = 4K; } >RAM
	.sstack (NOLOAD) : { . = 4K; } >RAM
	.data ALIGN(256) : { *(.data) } >RAM AT>ROM
	.bss ALIGN(256) : { KEEP(*(.bss)) KEEP(*(.bss*)) KEEP(*(COMMON)) } >RAM

	/* Symbols used for loading data by the loader */
	_vectors = ADDR(.vectors);
	_evectors = ADDR(.vectors) + SIZEOF(.vectors);
	_lvectors = LOADADDR(.vectors);
	_data = ADDR(.data);
	_edata = ADDR(.data) + SIZEOF(.data);
	_ldata = LOADADDR(.data);
	_bss = ADDR(.bss);
	_ebss = ADDR(.bss) + SIZEOF(.bss);
	_SSP = ADDR(.sstack) + SIZEOF(.sstack);
	_USP = ADDR(.ustack) + SIZEOF(.ustack);
}
