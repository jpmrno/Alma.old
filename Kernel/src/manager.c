#include <manager.h>
#include <define.h>
#include <output.h>

unsigned int manager_write(char * string, unsigned int length) {
	int i = 0;

	while(i < length && string[i]) {
		out_printf("%c", string[i++]);
	}

	return i;
}
