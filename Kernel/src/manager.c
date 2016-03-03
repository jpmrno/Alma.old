#include <manager.h>
#include <define.h>
#include <output.h>
#include <keyboard.h>
#include <limits.h>

void manage_key(key_st * key) {
	if(key->type == _KEY_TYPE_PRINTABLE) {
		out_printf("%c", key->value);	
	}
}

unsigned int manage_read(char * buffer, unsigned int length) {

}

unsigned int manage_write(char * string, unsigned int length) {
	int i = 0;
	int printed = 0;

	if(length == UINT_MAX) {
		return out_printf(string);
	}

	while(i < length && string[i]) {
		printed += out_printf("%c", string[i++]);
	}

	return printed;
}
