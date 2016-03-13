#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include <sys_calls.h>
#include <sys_io.h>
#include <sys_screen.h>
#include <sys_time.h>

int sysread(char * buffer, int length);
int syswrite(char * string, int length);

int systime(int operation, time_st * time);

int systerminal_select(int index);
void systerminal_clear();
void systerminal_color(int operation, style_st color);
int systerminal_cursor(cursor_st cursor);

#endif