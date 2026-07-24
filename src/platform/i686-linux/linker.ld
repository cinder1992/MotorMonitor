SECTIONS
{
	ENTRY(_start)

	.text 0x400000 : { *(.text) *(.text*) }
	.rodata ALIGN(4K) : { *(.rodata) *(.rodata*) }
	.data ALIGN(4K) : { *(.data) *(.data*) }
	.bss ALIGN(4K) : { *(.bss) *(COMMON) }

	/*EH FRAME INFO*/
	.eh_frame_hdr : {*(.eh_frame_hdr)}
	.eh_frame : {*(.eh_frame)}

	/* INIT and FINI arrays */
	/* Include the list of initialization functions sorted. */
	.init_array :
	{
		crti.o(.init_array)
		KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .init_array.*)))
		KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .init_array))
		crtn.o(.init_array)
	}

	/* Include the list of termination functions sorted. */
	.fini_array :
	{
		crti.o(.fini_array)
		KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .fini_array.*)))
		KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .fini_array))
		crtn.o(.fini_array)
	}

	/*DWARP Debug info*/
	.debug_abbrev 0 : {*(.debug_abbrev)}
	.debug_aranges 0 : {*(.debug_aranges)}
	.debug_frame 0 : {*(.debug_frame)}
	.debug_info 0 : {*(.debug_info)}
	.debug_line 0 : {*(.debug_line)}
	.debug_loc 0 : {*(.debug_loc)}
	.debug_macinfo 0 : {*(.debug_macinfog)}
	.debug_pubnames 0 : {*(.debug_pubnames)}
	.debug_pubtypes 0 : {*(.debug_pubtypes)}
	.debug_ranges 0 : {*(.debug_ranges)}
	.debug_str 0 : {*(.debug_str)}
	.debug_types 0 : {*(.debug_types)}

}
