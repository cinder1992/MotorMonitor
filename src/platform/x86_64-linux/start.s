.title "x86_64-linux: _start"

.text

.extern main

.globl _start

_start:
	call main
	#Returned from main, exit gracefully
	movq SYS_EXIT, %rax
	movq EXIT_CODE, %rdi
	syscall


.data
	.set SYS_EXIT, 60
	.set EXIT_CODE, 0
.end
