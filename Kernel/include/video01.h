#ifndef _VIDEO_DRIVER_01_H_
#define _VIDEO_DRIVER_01_H_

#include <define.h>
#include <colors.h>

#define SYSTEM_VIDEO_ROWS 25
#define SYSTEM_VIDEO_COLUMNS 80
#define SYSTEM_VIDEO_SIZE (SYSTEM_VIDEO_ROWS * SYSTEM_VIDEO_COLUMNS)
#define SYSTEM_VIDEO_STYLE_DEFAULT 0x0F

#define SYSTEM_ERROR_VIDEO_CURSOR_INVALID -1
#define SYSTEM_ERROR_VIDEO_SHAPE_INVALID -2

typedef uint8_t tSysVideoStyle;

typedef enum {
	SYSTEM_VIDEO_CURSOR_SHAPE_SQUARE, SYSTEM_VIDEO_CURSOR_SHAPE_UNDERSCORE
} tSysVideoCursorShape;

void video_init();
void video_clear();

void video_cursor_show(int boolean);
int video_cursor_set(unsigned int position);
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
