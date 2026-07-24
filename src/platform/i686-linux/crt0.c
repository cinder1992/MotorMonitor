extern void _init(void);
extern void _fini(void);
extern void main(void);

__attribute__((naked)) void _start(void) {
	_init();
	main();
	_fini();
	register int retval asm("%eax") = 1; //SYSCALL_EXIT
	register int exit_code asm("%ebx") = 0; //Return code is forced to 0
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(exit_code)
		: "memory"
	);
}

