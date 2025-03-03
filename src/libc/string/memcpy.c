#include <string.h>

void *memcpy(void* restrict dest, const void* src, size_t num) {
	// Cast src and dst to unsigned char *
	unsigned char *dest_c = (unsigned char*)dest;
	unsigned char *src_c = (unsigned char*)src;

	for(size_t i = 0; i < num; i++) {
		dest_c[i] = src_c[i];
	}

	return dest;
}
