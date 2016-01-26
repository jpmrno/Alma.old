#include <terminal01.h>
#include <stdarg.h>

#define TERMINAL_MAX 3 // TODO: Cambiar nombre?
#define TERMINAL_DEFAULT 0 // TODO: Cambiar nombre?

#define _OUTPUT_ERROR_TERMINAL_INVALID -1 // TODO: Cambiar de lugar

static terminal_st terminals[TERMINAL_MAX] = {{0}, {0}};
terminal_st * terminal_active; // TODO: A futuro inicializar

static int sleep_enabled = TRUE;
static int sleep_active = FALSE;
static int sleep_trigger = 10;

void out_init() {
	int i;

	//video_init(); // TODO: Kernel o aca?

	for(i = 0; i < TERMINAL_MAX; i++) {
		terminal_init(&terminals[i]);
	}

	terminal_show(&terminals[TERMINAL_DEFAULT]);
}

int out_select(int terminal_desired) {
	if(terminal_desired <= TERMINAL_MAX) {
		return _OUTPUT_ERROR_TERMINAL_INVALID;
	}

	terminal_show(&terminals[terminal_desired]);
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
					terminal_print(terminal_active, va_arg(arg, char *));
					break;
				case 'c':
					terminal_write(terminal_active, va_arg(arg, int));
					break;
				case 'd':
					terminal_digit(terminal_active, va_arg(arg, int), BASE_DECIMAL);
					break;
				case 'h':
					terminal_digit(terminal_active, va_arg(arg, int), BASE_HEXADECIMAL);
					break;
				case 'b':
					terminal_digit(terminal_active, va_arg(arg, int), BASE_BINARY);
					break;
				case '%':
					terminal_write(terminal_active, symbol);
					break;
			}
		} else {
			terminal_write(terminal_active, fmt[i]);
		}

		i++;
	}
	va_end(arg);

	return i - 1;
}

void out_cursor_lock() {

}

void out_cursor_shape() {

}

int out_sleep_isEnabled() {
	return sleep_enabled;
}

void out_sleep_enabled(int boolean) {
	sleep_enabled = boolean ? TRUE : FALSE;
}

int out_sleep_isActive() {
	return sleep_active;
}

void out_sleep() { // TODO: Screen Saver

}

void out_wake() {

}
