#ifndef _VIDEO_DRIVER_01_H_
#define _VIDEO_DRIVER_01_H_

#include <define.h>
#include <colors.h>

#define SYSTEM_VIDEO_ROWS 25
#define SYSTEM_VIDEO_COLUMNS 80
#define SYSTEM_VIDEO_SIZE (SYSTEM_VIDEO_ROWS * SYSTEM_VIDEO_COLUMNS)
#define SYSTEM_VIDEO_STYLE_DEFAULT 0x07

#define SYSTEM_ERROR_VIDEO_CURSOR_INVALID -1

typedef uint8_t vstyle_t;

void video_init();
void video_clear();

void video_cursor_show(int boolean);
int video_cursor_set(unsigned int position);
int video_cursor_get();

int video_put(unsigned int position, char character);
int video_putWithStyle(unsigned int position, char character, vstyle_t style);
char video_get(unsigned int position);

int video_style_put(unsigned int position, vstyle_t style);
int video_style_get(unsigned int position);
int video_color_put(unsigned int position, vstyle_t color);
int video_color_get(unsigned int position);
int video_bg_put(unsigned int position, vstyle_t bg);
int video_bg_get(unsigned int position);

#endif
