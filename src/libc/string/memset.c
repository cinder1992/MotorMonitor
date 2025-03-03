#include <string.h>

void *memset(void* dest, int val, size_t num) {
	unsigned char *dest_c = (unsigned char *)dest;

	for(size_t i = 0; i < num; i++) {
		dest_c[i] = (unsigned char)val;
	}
	return dest;
}


