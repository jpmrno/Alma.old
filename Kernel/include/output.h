#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <stdarg.h>
#include <colors.h>

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
int out_vprintf(char * fmt, va_list arg); // TODO: 

void out_box_top();
void out_box_bottom();
void out_box_line(char * fmt, ...);

int out_color_text(style_st color);
int out_color_bg(style_st color);
int out_cursor_shape(shape_st cursor);

void out_cursor_lock();

int out_sleep_init();
int out_sleep_step();
int out_sleep_stop();
int out_sleep_isActive();
int out_sleep_set(char * text, int boolean);
int out_sleep_reset();

#endif