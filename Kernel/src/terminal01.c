#include <stdarg.h>

#define _VIDEO_CURSOR_IN_LAST_POSITION(x) ((x) == (_VIDEO_SIZE - 1)) // TODO: In video.h

static void terminal_write(terminal_st * terminal, char character);
static void terminal_writter(terminal_st * terminal, char character);
static int terminal_print(terminal_st * terminal, char * string);

int terminal_printf(terminal_st * terminal, char * fmt, ...) {
    char symbol;
    int i = 0;
    va_list arg;

    va_start(arg, fmt);
    while(fmt[i] != 0) {
		if(fmt[i] == '%') {
			symbol = fmt[++i];
		    switch(symbol) {
		    	case 's':
					terminal_print(terminal, va_arg(arg, char *));
					break;
				case 'c':
					terminal_write(terminal, va_arg(arg, int));
					break;
				case 'd':
					terminal_putInBase(terminal, va_arg(arg, int), BASE_DECIMAL);
					break;
				case 'x':
					terminal_putInBase(terminal, va_arg(arg, unsigned int), BASE_HEXADECIMAL);
					break;
				case 'b':
					terminal_putInBase(terminal, va_arg(arg, unsigned int), BASE_BINARY);
					break;
				case '%':
					terminal_write(terminal, symbol);
					break;
		    }
		} else {
			terminal_write(terminal, fmt[i]);
		}

		i++;
    }
    va_end(arg);

    return i - 1;
}

static void terminal_write(terminal_st * terminal, char character) {
	int tab = TAB_SIZE;

	switch(character) {
		case '\n': // New line
			terminal_newline(terminal);
			break;

		case '\t': // Tab
			while(tab--) {
				terminal_writter(terminal, ' '); // TODO: 
			}
			break;

		case '\b': // Backspace
			if (getCursor() > cursorLockedAt) { // TODO: 
				terminal_delete(terminal);
			}
			break;

		default: // Normal Character
			terminal_writter(terminal, character);
			break;
	}
}

static void terminal_writter(terminal_st * terminal, char character) {
	// If cursor is in last position -> shifts up the page (1)
	if(_VIDEO_CURSOR_IN_LAST_POSITION(terminal.cursor)) {
		terminal_shift(terminal, 1); // TODO: Or -1
	}

	terminal->screen[terminal->cursor].character = character;
	terminal->screen[terminal->cursor].style = terminal.style;

	if(terminal == terminal_active) {
		video_putWithStyle(terminal->cursor, character, terminal->style);
		video_cursor_put(terminal->cursor + 1);
	}

	terminal->cursor++;
}

static int terminal_print(terminal_st * terminal, char * string) {
	int i = 0;

	while(string[i]) {
		terminal_write(terminal, string[i++]);
	}

	return i;
}

static void terminal_putInBase(terminal_st * terminal, , unsigned int base) {

}

static void terminal_newline(terminal_st * terminal) {

}

void terminal_shift(terminal_st * terminal, int lines) {

}

void terminal_delete(terminal_st * terminal) {

}

void terminal_show(terminal_st * terminal) {
	int i;

	// Send to video
	for(i = 0; i < _VIDEO_SIZE; i++) {
		pixel_st pixel = terminal->screen[i];
		video_putWithStyle(i, pixel.character, pixel.style);
	}

	video_cursor_put(terminal->cursor);
	video_cursor_show(terminal->cursor_shown);
	video_cursor_shape(terminal->cursor_shape);
	terminal_actual = terminal;
}

void terminal_hide() {
	video_clear();
	video_cursor_enable(FALSE);
}
