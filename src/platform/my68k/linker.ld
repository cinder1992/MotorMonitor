MEMORY
{
    VECTBL (r) : ORIGIN = 0, LENGTH = 0x400
    ROM (rx) : ORIGIN = 0x400, LENGTH = 1M - 0x400
    RAM (rwx) : ORIGIN = 0x100000, LENGTH = 1M
}

SECTIONS
{
    ENTRY(_start)
    _SSP = ORIGIN(RAM)+LENGTH(RAM);
    _USP = _SSP - 4k;
    .vectors : {*(.vectors)} > VECTBL
    .text : {*(.text) *(.rodata)} > ROM
    .data : {*(.data)} > RAM AT > ROM
    .bss : {*(.bss) *(COMMON)} > RAM
    _data = ADDR(.data);
    _edata = ADDR(.data) + SIZEOF(.data);
    _ldata = LOADADDR(.data);
    _bstart = ADDR(.bss);
    _bend = ADDR(.bss) + SIZEOF(.bss);
}
