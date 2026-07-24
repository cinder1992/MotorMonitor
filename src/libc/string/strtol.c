#include <string.h>
#include <ctype.h>

long strtol(const char* str, char** str_end, int base) {
	*str_end = (char*)str;
	int negate = 0;
	long retval = 0;
	if(base > 36) return 0; //Base must be less than 36!
	while(isspace(**str_end)) {(*str_end)++;} //Skip leading whitespace
	if(**str_end == '+') {(*str_end)++;} //Skip leading +
	else if(**str_end == '-') {negate = 1; (*str_end)++;} //negate result
	if(base == 0 || base == 8 || base == 16) { //Determine base
		if((*str_end)[0] == '0' && toupper((*str_end)[1]) == 'X' && base != 8){base = 16; *str_end += 2;}
		else if((*str_end)[0] == '0' && base != 16) {base = 8; (*str_end)++;}
		else {base = 10;}
	}

	//finally, parse our digits!
	while(isalnum(**str_end)) {
		if(isalpha(**str_end)) {
			//validate range
			if(toupper(**str_end)-'A' > base-1) break;
			retval *= (long)base;
			retval += toupper(**str_end) - 'A' + 10; 
			(*str_end)++;
		} else { //isdigit
			 retval *= (long)base;
			 retval += **str_end - '0';
			 (*str_end)++;
		}
	}
	if(negate == 1) retval = -retval;
	return retval;
}
