#include <manager.h>
#include <define.h>
#include <limits.h>
#include <output.h>
#include <keyboard.h>
#include <rtc.h>
#include <sys_io.h>
#include <sys_time.h>

static unsigned int manage_read_stdin(char * buffer, unsigned int length);
static unsigned int manage_write_stdout(const char * string, unsigned int length);

static int manage_terminal_select(int index);
static int manage_terminal_color(int operation, style_st color);
static int manage_terminal_cursor(shape_st cursor);

static int key_print_enabled = TRUE;
static int key_buffer_enabled = TRUE;
static int terminal_isWriting = FALSE;

void manage_time() {

}

void manage_key(key_st * key) {
	if(key->type == _KEY_TYPE_PRINTABLE) {
		if(key_buffer_enabled) {
			if (key->value == '\b') {
				// If the key cannot be erased, nothing is done for now.
				keyboard_delete();
			} else {
				// If the key cannot be buffered, nothing is done for now.
				keyboard_write(key);
			}
		}

		if(key_print_enabled) {
			out_printf("%c", key->value);				
		}
	}
}

unsigned int manage_read(unsigned int fd, char * buffer, unsigned int length) {
	switch(fd) {
		case _FILEDESCRIPTOR_STDIN:
			return manage_read_stdin(buffer, length);
	}

	return 0;
}

unsigned int manage_write(unsigned int fd, const char * string, unsigned int length) {
	switch(fd) {
		case _FILEDESCRIPTOR_STDOUT:
			return manage_write_stdout(string, length);
	}

	return 0;
}

int manage_rtc(int operation, time_st * time) {
	switch(operation) {
		case _TIME_OPERATION_SET:
			return ERROR_OCCURRED(rtc_write(time)) ? _TIME_OPERATION_ERROR : OK;

		case _TIME_OPERATION_GET:
			return ERROR_OCCURRED(rtc_read(time)) ? _TIME_OPERATION_ERROR : OK;
	}

	return _TIME_OPERATION_INVALID;
}

int manage_terminal(int operation, int value) {
	switch(operation) {
		case _TERMINAL_OPERATION_SELECT:
			manage_terminal_select(value);
			break;
		case _TERMINAL_COLOR_OPERATION_STYLE:
		case _TERMINAL_COLOR_OPERATION_TEXT:
		case _TERMINAL_COLOR_OPERATION_BG:
			manage_terminal_color(operation, (style_st) value);
			break;
		case _TERMINAL_OPERATION_CURSOR:
			manage_terminal_cursor((shape_st) value);

		default:
			return _TERMINAL_OPERATION_INVALID;
	}

	return OK;
}

static unsigned int manage_read_stdin(char * buffer, unsigned int length) {
	int i = 0;

	while(!keyboard_canRead());

	while(i < length && keyboard_canRead()) {
		buffer[i++] = keyboard_read();
	}

	return i;
}

static unsigned int manage_write_stdout(const char * string, unsigned int length) {
	int printed = 0, i = 0;

	terminal_isWriting = TRUE;

	if(length == UINT_MAX) {
		printed = out_printf(string);
	} else {
		while(i < length && string[i]) {
			printed += out_printf("%c", string[i++]);
		}
	}

	out_cursor_lock();
	terminal_isWriting = FALSE;

	return printed;
}

static int manage_terminal_select(int index) {
	return ERROR_OCCURRED(out_select(index)) ? _TERMINAL_OPERATION_ERROR : OK;
}

static int manage_terminal_color(int operation, style_st color) {
	switch(operation) {
		case _TERMINAL_COLOR_OPERATION_STYLE:
			out_color_text(_VIDEO_COLOR_GETTER(color));
			out_color_bg(_VIDEO_BG_TO_COLOR(color));
			break;

		case _TERMINAL_COLOR_OPERATION_TEXT:
			out_color_text(_VIDEO_COLOR_GETTER(color));
			break;

		case _TERMINAL_COLOR_OPERATION_BG:
			out_color_bg(_VIDEO_COLOR_GETTER(color));
			break;

		default:
			return _TERMINAL_OPERATION_INVALID;
	}

	return OK;
}

static int manage_terminal_cursor(shape_st cursor) {
	return ERROR_OCCURRED(out_cursor_shape(cursor)) ? _TERMINAL_OPERATION_ERROR : OK;
}
