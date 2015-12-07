#ifndef _TERMINAL_H_NEW
#define _TERMINAL_H_NEW // TODO: Change

#include <define.h>
#include <video01.h> // TODO: No me gusta esto aca

typedef struct {
	unsigned int cursor;
	int cursor_shown;
	style_st style;
	screen_st screen;
	tSysVideoCursorShape cursor_shape;
} terminal_st;

void terminal_init(terminal_st * terminal);
void terminal_show(terminal_st * terminal);
void terminal_hide();

int terminal_printf(terminal_st * terminal, char * fmt, ...);

void terminal_shift(terminal_st * terminal, int lines);
void terminal_delete(terminal_st * terminal);

#endif