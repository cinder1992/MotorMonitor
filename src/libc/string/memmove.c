#include <string.h>

void *memmove(void* dest, const void* src, size_t num) {
	unsigned char *dest_c = (unsigned char *)dest;
	unsigned char *src_c = (unsigned char *)src;

	if(dest < src) {
		dest = memcpy(dest, src, num);
	} else if(dest > src) {
		for(size_t i = num; i > 0; i--) {
			dest_c[i] = src_c[i];
		}
	}
	return dest;
}
