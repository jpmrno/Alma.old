#ifndef _VIDEO_DRIVER_01_H_
#define _VIDEO_DRIVER_01_H_

#include <define.h>
#include <colors.h>

#define _VIDEO_ROWS 25
#define _VIDEO_COLUMNS 80
#define _VIDEO_SIZE (_VIDEO_ROWS * _VIDEO_COLUMNS)

#define _ERROR_VIDEO_CURSOR_INVALID -1
#define _ERROR_VIDEO_SHAPE_INVALID -2

// TODO: Docs

typedef uint8_t tSysVideoStyle;

typedef enum {
	_VIDEO_CURSOR_SHAPE_SQUARE, _VIDEO_CURSOR_SHAPE_UNDERSCORE, _VIDEO_CURSOR_SHAPE_DOT
} tSysVideoCursorShape;

typedef struct {
    uint8_t character;
    uint8_t style;
} screen_t;

void video_init();
void video_clear();

void video_cursor_show(int boolean);
int video_cursor_put(unsigned int position);
int video_cursor_get();

int video_cursor_shape(tSysVideoCursorShape shape);

int video_put(unsigned int position, char character);
int video_putWithStyle(unsigned int position, char character, tSysVideoStyle style);
char video_get(unsigned int position);

int video_style_put(unsigned int position, tSysVideoStyle style);
int video_style_get(unsigned int position);
int video_color_put(unsigned int position, tSysVideoStyle color);
int video_color_get(unsigned int position);
int video_bg_put(unsigned int position, tSysVideoStyle bg);
int video_bg_get(unsigned int position);

#endif
