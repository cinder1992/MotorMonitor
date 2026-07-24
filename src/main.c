#include <stdio.h>
#include <main.h>
#include <string.h>
#include <stdlib.h>

const char signon_str[] = "COACH Monitor program " COACH_VERSION "\n"; 
const char compile_str[] = "Compiled with " _PLATFORM_CC " v" _PLATFORM_CC_VERSION " on " __DATE__ " at " __TIME__ "\n";

const char* teststr1 = "1000";
const char* teststr2 = "-32768";
const char* teststr3 = "0xBADF00D";

void main() {
	char* end;
	printf(signon_str);
	printf(compile_str);
	int strtoul3 = (int)strtoul(teststr3,&end,0);
	int strtoul2 = (int)strtoul(teststr2,&end,0);
	int strtoul1 = (int)strtoul(teststr1,&end,0);
	printf("%d,%d,%x\n", strtoul1, strtoul2, strtoul3);
	//printf("sizeof(int): %x, sizeof(long): %x, sizeof(long long): %x\n", (int)sizeof(int), (int)sizeof(long), (int)sizeof(long long));
}
