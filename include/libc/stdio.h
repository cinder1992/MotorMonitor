#ifndef _STDIO_H
#define _STDIO_H 1

//both clang and GCC provide these defines to prevent typedef collisions
//In our case, we're only using GCC, but llvm will hopefully get support for these
//once m68k support hits mainline
#define __need_size_t
#define __need_NULL
#include <stddef.h>

#define __need_platform_defines
#include <platform.h>

#define FOPEN_MAX _PLATFORM_FOPEN_MAX
#define FILENAME_MAX _PLATFORM_FILENAME_MAX
#define BUFSIZ _PLATFORM_BUFSIZ
#define L_tempnam _PLATFORM_L_tempnam

#define _IOFBF 2
#define _IOLBF 1
#define _IONBF 0
//#define _IOSTR 3

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define EOF -1

typedef off_t fpos_t;

typedef struct {
	void* _buf;
	size_t _buf_size;
	size_t _buf_cur;
	int _buf_unget;
	int _fd;
	fpos_t _fileptr;
	int _ferror;
	union {
		unsigned int _flags;
		struct {
			unsigned int _fvalid : 1;
			unsigned int _bufmode : 2;
			unsigned int _fl_r : 1;
			unsigned int _fl_w : 1;
			unsigned int _fl_a : 1;
			unsigned int _fl_e : 1;
			unsigned int _fl_mode: 1;
		};
	};
	int (*_read)(int,unsigned char*,size_t);
	int (*_write)(int,const unsigned char*,size_t);
	int (*_close)(int);
	int (*_flush)(int);
	off_t (*_seek)(int,off_t,unsigned int);
} FILE;

__attribute__((__visibility__("hidden"))) extern FILE _platform_stdin_file;
__attribute__((__visibility__("hidden"))) extern FILE _platform_stdout_file;
__attribute__((__visibility__("hidden"))) extern FILE _platform_stderr_file;

#define stdin (&_platform_stdin_file)
#define stdout (&_platform_stdout_file)
#define stderr (&_platform_stderr_file)

//getc family
extern int fgetc(FILE*);
#define getc(Z) fgetc(Z)
extern int getchar(void);
extern int ungetc(int, FILE*);

//putc family
extern int fputc(int, FILE *);
#define putc(X,Y) fputc(X,Y)
extern int putchar(int);

//fgets family
extern char* fgets(char* __restrict, int, FILE* __restrict);
//gets will not be implemented, is deprecated in C99 anyways

//puts family
extern int fputs(const char* __restrict, FILE* __restrict);
extern int puts(const char* __restrict);

//fprintf family
extern int vfprintf(FILE* __restrict, const char* __restrict, __builtin_va_list);
extern int vprintf(const char* __restrict, __builtin_va_list);
extern int fprintf(FILE* __restrict, const char* __restrict, ...);
extern int printf(const char* __restrict, ...);

//fscanf family
extern int vfscanf(FILE* __restrict,const char* __restrict, __builtin_va_list);
extern int vscanf(const char* __restrict, __builtin_va_list);
extern int fscanf(FILE* __restrict, const char* __restrict, ...);
extern int scanf(const char* __restrict, ...);

//sprintf family
//TODO
extern int vsnprintf(char* __restrict, size_t, const char* __restrict, __builtin_va_list);
extern int snprintf(char* __restrict, size_t, const char* __restrict, ...);
//both sprintf and vsprintf will not be implemented. Why? Both are footguns.
//don't know what a footgun is? Well it's a function that exists for the sole reason
//of shooting yourself in the foot.

//sscanf family
//TODO
extern int vsscanf(const char* __restrict, const char* __restrict, __builtin_va_list);
extern int sscanf(const char* __restrict, const char* __restrict, ...);

//file access
//TODO
#if _PLATFORM_HAS_FS
extern FILE* fopen(const char* __restrict, const char* __restrict);
extern FILE* freopen(const char* __restrict, const char* __restrict, FILE* __restrict);
extern int fclose(FILE*);
extern int fflush(FILE*);
extern int setbuf(FILE* __restrict, char* __restrict);
#endif //_PLATFORM_HAS_FS
extern int setvbuf(FILE* __restrict, char* __restrict, int, size_t);

//direct file access
//TODO
extern size_t fread(void* __restrict, size_t, size_t, FILE* __restrict);
extern size_t fwrite(const void* __restrict, size_t, size_t, FILE* __restrict);

//file seeking
//TODO
#if _PLATFORM_HAS_FS
extern long ftell(FILE*);
extern int fgetpos(FILE* __restrict, fpos_t* __restrict);
extern int fsetpos(FILE*, const fpos_t*);
extern int fseek(FILE*, long, int);
extern void rewind(FILE*);
#endif //_PLATFORM_HAS_FS
//file error handling
//TODO
extern void clearerr(FILE*);
extern int feof(FILE*);
extern int ferror(FILE*);
extern int perror(FILE*);

//file operations
//TODO
extern int remove(const char*);
extern int rename(const char*, const char*);
extern FILE* tmpfile(void);
extern char* tmpnam(char*);

#endif //_STDIO_H
