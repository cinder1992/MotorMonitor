#include <stdio.h>
#include <ctype.h>

char* fgets(char* __restrict str, int len, FILE* __restrict file) {
	int idx = 0;
	int val;
	for(int i = 0; i < len; i++) {
		val = fgetc(file);
		if(isgraph(val)){
			str[idx] = (char)val;
			idx++;
		} else {
			str[idx] = '\0';
			break;
		}
	}
	str[idx] = '\0';
	return str;
}
