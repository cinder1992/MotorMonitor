#include <stdio.h>
#include "platform/my68k/mfp.h"

void* _platform_mem = (void*)0;


FILE _platform_stdin_file = {
	._buf_size = 0,
	._fd = 0,
	._buf_unget = '\0',
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

int _platform_read(int fdes,unsigned char* buf,size_t count) {
	size_t i;
	if(fdes != 0) return -1;
	for(i=0; i < count; i++) {
		int tmp = (int)mfp_getc();
		if(tmp == '\x04') return 0;
		buf[i] = tmp;
	}
	return (int)i;
}

int _platform_write(int fdes,const unsigned char* buf,size_t count) {
	size_t i;
	if(fdes != 1 && fdes != 2) return -1;
	for(i=0; i < count; i++) {
		mfp_putc(buf[i]);
	}
	return (int)i;
}
int _platform_close(int fdes) {
	(void)fdes; //Silence, warning
	return 0;
}
int _platform_flush(int fdes) {
	(void)fdes; //Silence, warning
	return 0;
}
off_t _platform_seek(int fdes,off_t offs, unsigned int whence) {
	(void)fdes; (void)offs; (void)whence; //Silence, warnings
	return 0;
}
