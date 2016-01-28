#include <output.h>
#include <terminal.h>
#include <stdarg.h>
#include <strings.h>

// TODO: Temporal
#define BASE_BINARY 2 // TODO: Cambiar de lugar! numbers.h en shared lib?
#define BASE_DECIMAL 10
#define BASE_HEXADECIMAL 16

#define SLEEP_TEXT_DEFAULT " ..|.. "

// Terminal vars
static terminal_st terminals[_OUTPUT_TERMINAL_MAX] = {{0}, {0}};
static int terminal_active = _OUTPUT_TERMINAL_DEFAULT; // TODO: A futuro inicializar
// ^^^ Terminal vars ^^^

// Sleep vars
static int sleep_active = FALSE;
static char * sleep_text = SLEEP_TEXT_DEFAULT;
static int sleep_loop = TRUE;
// ^^^ Sleep vars ^^^

void out_init() {
	int i;

	for(i = 0; i < _OUTPUT_TERMINAL_MAX; i++) {
		terminal_init(&terminals[i]);
	}

	terminal_active = _OUTPUT_TERMINAL_DEFAULT;
	terminal_show(&terminals[terminal_active]);
}

int out_select(int terminal_desired) {
	if(terminal_desired <= _OUTPUT_TERMINAL_MAX) {
		return _OUTPUT_ERROR_TERMINAL_INVALID;
	}

	terminal_active = terminal_desired;
	terminal_show(&terminals[terminal_desired]);

	return OK;
}

int out_printf(char * fmt, ...) { // TODO: How to set styles
    char symbol;
    int i = 0;
    va_list arg;

    va_start(arg, fmt);
    while(fmt[i] != 0) {
		if(fmt[i] == '%') {
			symbol = fmt[++i];
		    switch(symbol) {
		    	case 's':
					terminal_print(&terminals[terminal_active], va_arg(arg, char *));
					break;
				case 'c':
					terminal_write(&terminals[terminal_active], va_arg(arg, int));
					break;
				case 'd':
					terminal_digit(&terminals[terminal_active], va_arg(arg, int), BASE_DECIMAL);
					break;
				case 'h':
					terminal_digit(&terminals[terminal_active], va_arg(arg, int), BASE_HEXADECIMAL);
					break;
				case 'b':
					terminal_digit(&terminals[terminal_active], va_arg(arg, int), BASE_BINARY);
					break;
				case '%':
					terminal_write(&terminals[terminal_active], symbol);
					break;
			}
		} else {
			terminal_write(&terminals[terminal_active], fmt[i]);
		}

		i++;
	}
	va_end(arg);

	return i - 1;
}

void out_cursor_lock() { // TODO: 

}

void out_cursor_shape() { // TODO: 

}

// int out_sleep_isEnabled() { // TODO: En manager?
// 	return sleep_enabled;
// }

// void out_sleep_enabled(int boolean) { // TODO: En manager?
// 	if(sleep_active) {
// 		return _OUTPUT_ERROR_SLEEP_ACTIVE;
// 	}

// 	sleep_enabled = boolean ? TRUE : FALSE;
// }

// int out_sleep_time_set(unsigned int time) {
// 	if(sleep_active) {
// 		return _OUTPUT_ERROR_SLEEP_ACTIVE;
// 	}

// 	if(time < _OUTPUT_SLEEP_TIME_MIN) {
// 		return _OUTPUT_ERROR_SLEEP_TIME;
// 	}

// 	sleep_trigger = time;

// 	return OK;
// }

// int out_sleep_time_get() {
// 	return sleep_trigger;
// }

int out_sleep_init() { // TODO: Screen Saver
	if(sleep_active) {
		return _OUTPUT_ERROR_SLEEP_ACTIVE;
	}

	sleep_active = TRUE;
	terminal_hide();

	terminal_print(&terminals[terminal_active], sleep_text); // TODO: 

	return OK;
}

int out_sleep_step() {
	if(!sleep_active) {
		return _OUTPUT_ERROR_SLEEP_NOT_ACTIVE;
	}
	
	if(sleep_loop) {
		terminal_print(&terminals[terminal_active], sleep_text);
	}

	return OK;
}

int out_sleep_stop() { // TODO: Screen Saver
	if(!sleep_active) {
		return _OUTPUT_ERROR_SLEEP_NOT_ACTIVE;
	}

	sleep_active = FALSE;

	return OK;
}

int out_sleep_isActive() {
	return sleep_active;
}

int out_sleep_loop(int boolean) {
	if(sleep_active) {
		return _OUTPUT_ERROR_SLEEP_ACTIVE;
	}

	sleep_loop = boolean ? TRUE : FALSE;

	return OK;
}

int out_sleep_text(char * text) { // TODO: 
	strcpy(sleep_text, text);

	return 0;
}
