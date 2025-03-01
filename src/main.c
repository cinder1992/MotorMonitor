#include <stdio.h>

void main() {
	const char str[] = "Hellorld!";
	int i = getchar();
	int j = 0;
	puts(str);
	while(1) {
		int val = scanf("%d %d", &i, &j);
		if(val != 2) {
			printf("Ohgodwhat %x", val);
			continue;
		}
		printf("0x%x 0x%x", i, j);
	}
}
