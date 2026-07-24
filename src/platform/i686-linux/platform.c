#include <stdio.h>
#include <platform.h>

char* _platform_ram[1024*1024];
void* _platform_mem = (void*)_platform_ram;

FILE _platform_stdin_file = {
	._buf_size = 0,
	._buf_unget = '\0',
	._fd = 0,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 1,
	._fl_w = 0,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek
};

FILE _platform_stdout_file = {
	._buf_size = 0,
	._fd = 1,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 0,
	._fl_w = 1,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek,
};

FILE _platform_stderr_file = {
	._buf_size = 0,
	._fd = 2,
	._fileptr = 0,
	._ferror = 0,
	._fvalid = 1,
	._bufmode = _IONBF,
	._fl_r = 0,
	._fl_w = 1,
	._fl_a = 0,
	._read = _platform_read,
	._write = _platform_write,
	._close = _platform_close,
	._flush = _platform_flush,
	._seek = _platform_seek,
};

#define SYSCALL_READ 3
#define SYSCALL_WRITE 4
#define SYSCALL_CLOSE 6
#define SYSCALL_FSYNC 118
#define SYSCALL_LSEEK 19

int _platform_read(int fdes, unsigned char* buf, size_t count) {
	register int retval asm("%eax") = SYSCALL_READ;
	register int ebx asm("%ebx") = fdes;
	register unsigned char* ecx asm("%ecx") = buf;
	register size_t edx asm("%edx") = count;
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(ebx), "r"(ecx), "r"(edx)
		: "memory"
	);
	return retval;
}

int _platform_write(int fdes, const unsigned char* buf, size_t count) {
	register int retval asm("%eax") = SYSCALL_WRITE;
	register int ebx asm("%ebx") = fdes;
	register const unsigned char* ecx asm("%ecx") = buf;
	register size_t edx asm("%edx") = count;
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(ebx), "r"(ecx), "r"(edx)
		: "memory"
	);
	return retval;
}


int _platform_close(int fdes) {
	register int retval asm("%eax") = SYSCALL_CLOSE;
	register int ebx asm("%ebx") = fdes;
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(ebx)
		: "memory"
	);
	return retval;
}

int _platform_flush(int fdes) {
	register int retval asm("%eax") = SYSCALL_FSYNC;
	register int ebx asm("%ebx") = fdes;
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(ebx)
		: "memory"
	);
	return retval;
}

off_t _platform_seek(int fdes, off_t offs, unsigned int whence) {
	register int retval asm("%eax") = SYSCALL_LSEEK;
	register int ebx asm("%ebx") = fdes;
	register off_t ecx asm("%ecx") = offs;
	register unsigned int edx asm("%edx") = whence;
	asm volatile(
		"int $0x80"
		: "+r"(retval)
		: "r"(retval), "r"(ebx), "r"(ecx), "r"(edx)
		: "memory"
	);
	return retval;
}
