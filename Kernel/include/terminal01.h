#ifndef _TERMINAL_H_
#define _TERMINAL_H_

typedef struct {
	unsigned int cursor;
	int cursor_shown;
	style_st style;
	screen_st screen;
} terminal_st;

int terminal_printf(terminal_st * terminal, char * fmt, ...);

#endif