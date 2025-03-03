#ifndef _STDIO_H
#define _STDIO_H 1

//both clang and GCC provide these defines to prevent typedef collisions
//In our case, we're only using GCC, but llvm will hopefully get support for these
//once m68k support hits mainline
#define __need_size_t
#define __need_NULL
#include <stddef.h>

#define EOF -1 //Futureproofing
#define stdin (FILE*)1
#define stdout (FILE*)2
#define stderr (FILE*)3
#define getc(Z) fgetc(Z)
#define putc(X,Y) fputc(X,Y)

typedef int FILE;

//platform-specific functions
extern int putchar(int);
extern int getchar(void);

extern int fputc(int, FILE *);

extern int fputs(const char*, FILE*);
extern int puts(const char*);


extern int fgetc(FILE*);
extern char* fgets(char* __restrict, int, FILE* __restrict);

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

#endif //_STDIO_H
