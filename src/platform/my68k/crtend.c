/* Simple x86_64-ELF ABI destructor runner */
/* borrowed from the OSDEV wiki */

typedef void (*func_ptr)(void);

func_ptr _init_array_end[0] __attribute__ ((used, section(".ctors"), aligned(sizeof(func_ptr)))) = { };
func_ptr _fini_array_end[0] __attribute__ ((used, section(".dtors"), aligned(sizeof(func_ptr)))) = { };
