#include <string.h>

int memcmp(const void *aptr, const void *bptr, size_t num) {
	const unsigned char *a_c = (const unsigned char *)aptr;
	const unsigned char *b_c = (const unsigned char *)bptr;
	for(size_t i = 0; i < num; i++) {
		if (a_c[i] != b_c[i]) {
			return a_c[i] < b_c[i] ? -1 : 1;
		}
	}
	return 0;
}
