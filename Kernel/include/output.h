#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#define _OUTPUT_TERMINAL_MAX 2
#define _OUTPUT_TERMINAL_DEFAULT 0

#define _OUTPUT_SLEEP_TIME_MIN 5

#define _OUTPUT_ERROR_TERMINAL_INVALID -1
#define _OUTPUT_ERROR_SLEEP_ACTIVE -2
#define _OUTPUT_ERROR_SLEEP_NOT_ACTIVE -3
#define _OUTPUT_ERROR_SLEEP_TIME -4

void out_init();
int out_select(int terminal_desired);

int out_printf(char * fmt, ...);

void out_cursor_lock();
void out_cursor_shape();

int out_sleep_init();
int out_sleep_step();
int out_sleep_stop();
int out_sleep_isActive();
int out_sleep_loop(int boolean);
int out_sleep_text(char * text);

#endif