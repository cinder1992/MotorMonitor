#ifndef _STRING_H
#define _STRING_H

//both clang and GCC provide these defines to prevent typedef collisions
//In our case, we're only using GCC, but llvm will hopefully get support for these
#define __need_size_t
#define __need_NULL
#include <stddef.h>

//TODO: Organize
extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, int, size_t);
extern void *memmove(void *, const void *, size_t);
extern int memcmp(const void *, const void *, size_t);
extern size_t strlen(const char*);
extern size_t strspn(const char*, const char*);
extern size_t strcspn(const char*, const char*);
extern char* strpbrk(const char*, const char*);
extern char* strtok(char*, const char*);
#endif
