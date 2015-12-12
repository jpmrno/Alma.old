#ifndef _VIDEO_DRIVER_01_H_
#define _VIDEO_DRIVER_01_H_

#include <define01.h>
#include <colors.h>

#define _VIDEO_ROWS 25
#define _VIDEO_COLUMNS 80
#define _VIDEO_SIZE (_VIDEO_ROWS * _VIDEO_COLUMNS)

#define _VIDEO_ERROR_CURSOR_INVALID -1
#define _VIDEO_ERROR_CURSOR_SHAPE_INVALID -2
#define _VIDEO_ERROR_RANGE_INVALID -3

#define _VIDEO_CURSOR_LAST_POSITION (_VIDEO_SIZE - 1)

// TODO: Docs

typedef uint8_t tSysVideoStyle; // TODO: Remove

typedef enum {
	_VIDEO_CURSOR_SHAPE_SQUARE, _VIDEO_CURSOR_SHAPE_UNDERSCORE, _VIDEO_CURSOR_SHAPE_DOT
} tSysVideoCursorShape;

#define _VIDEO_CURSOR_SHAPE_DEFAULT _VIDEO_CURSOR_SHAPE_SQUARE

typedef struct {
    uint8_t character;
    uint8_t style;
} pixel_st;

typedef pixel_st screen_st[_VIDEO_SIZE];

void video_init();
void video_clear();

void video_cursor_show(int boolean);
int video_cursor_put(unsigned int position);
int video_cursor_get();

int video_cursor_shape(tSysVideoCursorShape shape);

int video_write(unsigned int position, char character);
int video_writeWithStyle(unsigned int position, char character, tSysVideoStyle style);
char video_get(unsigned int position);

int video_style_put(unsigned int position, tSysVideoStyle style);
int video_style_get(unsigned int position);
void video_style_all(tSysVideoStyle style);
int video_style_range(unsigned int from, unsigned int to, tSysVideoStyle style);

int video_color_put(unsigned int position, tSysVideoStyle color);
int video_color_get(unsigned int position);
void video_color_all(tSysVideoStyle color);
int video_color_range(unsigned int from, unsigned int to, tSysVideoStyle color);

int video_bg_put(unsigned int position, tSysVideoStyle bg);
int video_bg_get(unsigned int position);
void video_bg_all(tSysVideoStyle bg);
int video_bg_range(unsigned int from, unsigned int to, tSysVideoStyle bg);

#endif
