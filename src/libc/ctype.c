#include <ctype.h>
#define TRUE 1 == 1
#define FALSE 1 == 0

int isalnum(int chr) {
	return isalpha(chr) || isdigit(chr);
}

int isalpha(int chr) {
	return  islower(chr) || isupper(chr);
}

int iscntrl(int chr) {
	return (chr <= '\x1F') || (chr == '\x7F');
}

int isdigit(int chr) {
	return (chr >= '0') && (chr <= '9');
}

int isgraph(int chr) {
	return (chr > '\x20') && (chr < '\x7F');
}

int islower(int chr) {
	return (chr >= 'a') && (chr <= 'z');
}

int isprint(int chr) {
	return isgraph(chr) || isspace(chr);
}

int ispunct(int chr) {
	return isgraph(chr) && !isalnum(chr);
}

int isspace(int chr) {
	switch(chr) {
		case ' ':
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			return TRUE;
			break;
		default:
			return FALSE;
	}
}

int isupper(int chr) {
	return (chr >= 'A') && (chr <= 'Z');
}
int isxdigit(int chr) {
	return
		((chr >= 'A') && (chr <= 'F')) ||
		((chr >= 'a') && (chr <= 'f')) ||
		isdigit(chr);
}
int tolower(int chr) {
	if(isupper(chr)) {
		return chr + '\x20';
	}
	return chr;
}

int toupper(int chr) {
	if(islower(chr)) {
		return chr - '\x20';
	}
	return chr;
}
