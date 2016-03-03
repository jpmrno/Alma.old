#include <manager.h>
#include <define.h>
#include <output.h>
#include <keyboard.h>
#include <limits.h>

static unsigned int manage_read_stdin(char * buffer, unsigned int length);
static unsigned int manage_write_stdout(char * string, unsigned int length);

static int key_print_enabled = TRUE;

void manage_time() {

}

void manage_key(key_st * key) {
	if(key->type == _KEY_TYPE_PRINTABLE) {
		if (key->value == '\b') {
			// If the key cannot be erased, nothing is done for now.
			keyboard_delete();
		} else {
			// If the key cannot be buffered, nothing is done for now.
			keyboard_write(key);
		}

		if(key_print_enabled) {
			out_printf("%c", key->value);				
		}
	}
}

unsigned int manage_read(int fd, char * buffer, unsigned int length) {
	switch(fd) {
		case _FILEDESCRIPTOR_STDIN:
			return manage_read_stdin(buffer, length);
	}

	return 0;
}

unsigned int manage_write(int fd, char * string, unsigned int length) {
	switch(fd) {
		case _FILEDESCRIPTOR_STDOUT:
			return manage_write_stdout(string, length);
	}

	return 0;
}

static unsigned int manage_read_stdin(char * buffer, unsigned int length) {

}

static unsigned int manage_write_stdout(char * string, unsigned int length) {
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
