#ifndef _PLATFORM_H
#define _PLATFORM_H 1
#define _PLATFORM_FOPEN_MAX 8
#define _PLATFORM_FILENAME_MAX 255
#define _PLATFORM_BUFSIZ 255
#define _PLATFORM_L_tempnam 255

#define _PLATFORM_CC PLATFORM_CC
#define _PLATFORM_CC_VERSION __VERSION__

#define __need_size_t
#define __need_NULL
#include <stddef.h>
typedef long off_t;

extern void* _platform_mem;
int _platform_read(int /*fdes*/,unsigned char* /*buf*/,size_t /*count*/);
int _platform_write(int /*fdes*/,const unsigned char* /*buf*/,size_t /*count*/);
int _platform_close(int /*fdes*/);
int _platform_flush(int /*fdes*/);
off_t _platform_seek(int /*fdes*/,off_t /*offs*/, unsigned int /*whence*/);
#endif //_PLATFORM_H
