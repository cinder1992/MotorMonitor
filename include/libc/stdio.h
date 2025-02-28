#ifndef _STDIO_H
#define _STDIO_H 1

//both clang and GCC provide these defines to prevent typedef collisions
//In our case, we're only using GCC, but llvm will hopefully get support for these
#define __need_size_t
#define __need_NULL
#include <stddef.h>

#define EOF -1 //Futureproofing
#define stdin (FILE*)0
#define stdout (FILE*)1
#define stderr (FILE*)2
#define getc(Z) fgetc(Z)
#define putc(X,Y) fputc(X,Y)

typedef int FILE;

//platform-specific functions
extern int putchar(int);
extern int getchar(void);

int fputc(int, FILE *);

int fputs(const char*, FILE*);
int puts(const char*);


int fgetc(FILE*);

int vfprintf(FILE*, const char* __restrict, __builtin_va_list);
int vprintf(const char* __restrict, __builtin_va_list);
int fprintf(FILE*, const char* __restrict, ...);
int printf(const char* __restrict, ...);

#endif //_STDIO_H
