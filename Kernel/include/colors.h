#ifndef _VIDEO_COLORS_H_
#define _VIDEO_COLORS_H_

#define _VIDEO_COLOR_BITS 4
#define _VIDEO_COLOR_GETTER(x) ((x) & 0x0F)
#define _VIDEO_BG_GETTER(x) ((x) & 0xF0)
#define _VIDEO_COLOR_TO_BG(x) (_VIDEO_COLOR_GETTER(x) << _VIDEO_COLOR_BITS)
#define _VIDEO_BG_TO_COLOR(x) (_VIDEO_BG_GETTER(x) >> _VIDEO_COLOR_BITS)
#define _VIDEO_STYLER_COLOR(x, y) (_VIDEO_BG_GETTER(x) +  _VIDEO_COLOR_GETTER(y))
#define _VIDEO_STYLER_BG(x, y) (_VIDEO_COLOR_GETTER(x) + _VIDEO_COLOR_TO_BG(y))
#define _VIDEO_STYLER(x, y) (_VIDEO_COLOR_GETTER(x) + _VIDEO_COLOR_TO_BG(y))

#define _VIDEO_COLOR_BRIGHTTEN(x) (_VIDEO_COLOR_GETTER(x) + 0x08)

enum video_color_st {
	_VIDEO_COLOR_BLACK = 0x00,
	_VIDEO_COLOR_BLUE,
	_VIDEO_COLOR_GREEN,
	_VIDEO_COLOR_CYAN,
	_VIDEO_COLOR_RED,
	_VIDEO_COLOR_PURPLE,
	_VIDEO_COLOR_BROWN,
	_VIDEO_COLOR_WHITE
};

#define _VIDEO_BG_DEFAULT 0x00
#define _VIDEO_COLOR_DEFAULT 0x07
#define _VIDEO_STYLE_DEFAULT (_VIDEO_BG_DEFAULT + _VIDEO_COLOR_DEFAULT)

#endif