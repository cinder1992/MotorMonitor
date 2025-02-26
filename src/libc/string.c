#include <string.h>

void *memcpy(void *dest, const void *src, size_t num) {
	// Cast src and dst to unsigned char *
	unsigned char *dest_c = (unsigned char*)dest;
	unsigned char *src_c = (unsigned char*)src;

	for(size_t i = 0; i < num; i++) {
		dest_c[i] = src_c[i];
	}

	return dest;
}

void *memset(void *dest, int val, size_t num) {
	unsigned char *dest_c = (unsigned char *)dest;

	for(size_t i = 0; i < num; i++) {
		dest_c[i] = (unsigned char)val;
	}
	return dest;
}

void *memmove(void *dest, const void *src, size_t num) {
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

int memcmp(const void *a, const void *b, size_t num) {
	const unsigned char *a_c = (const unsigned char *)a;
	const unsigned char *b_c = (const unsigned char *)b;
	for(size_t i = 0; i < num; i++) {
		if (a_c[i] != b_c[i]) {
			return a_c[i] < b_c[i] ? -1 : 1;
		}
	}
	return 0;
}

size_t strlen(const char* str) {
  size_t ret = 0;
  while( str[ret] != 0 ) {
    ret++;
  }
  return ret;
}
