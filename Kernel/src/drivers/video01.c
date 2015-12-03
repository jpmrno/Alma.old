#include <video01.h>
#include <liba.h>

// DEFINES
#define VIDEO_DIR 0xB8000

#define PORT_VIDEO_INDEX 0x3D4
#define PORT_VIDEO_DATA 0x3D5

// Cursor Registers
#define INDEX_CURSOR_START_REGISTER 0x0A
#define INDEX_CURSOR_END_REGISTER 0x0B
#define INDEX_CURSOR_LOCATION_HIGH_REGISTER 0x0E
#define INDEX_CURSOR_LOCATION_LOW_REGISTER 0x0F
// ^^^ Cursor Registers ^^^

// Cursor Shapes
// Square
#define CURSOR_SHAPE_SQUARE_START 0x00
#define CURSOR_SHAPE_SQUARE_END 0x1F
// Underscore
#define CURSOR_SHAPE_UNDERSCORE_START 0x0E
#define CURSOR_SHAPE_UNDERSCORE_END 0x1F
// Dot
#define CURSOR_SHAPE_DOT_START 0x07
#define CURSOR_SHAPE_DOT_END 0x1F
// ^^^ Cursor Shapes ^^^

#define COLOR_TO_BG(x) ((x) << COLOR_BITS)
#define BG_TO_COLOR(x) ((x) >> COLOR_BITS)

#define BYTE_FIRST_HALF(x) ((x) & 0x0F0)
#define BYTE_LAST_HALF(x) ((x) & 0x0F)
#define WORD_FIRST_HALF(x) ((x) & 0x0FF00)
#define WORD_LAST_HALF(x) ((x) & 0x0FF)
#define BYTE_LAST_5BITS(x) ((x) & 0x01F)

typedef struct {
    uint8_t character;
    uint8_t style;
} tSystemVideo;
// ^^^ DEFINES ^^^
 
// LOCAL FUNCTIONS
static void video_cursor_shape_changer(uint8_t start, uint8_t end);
static void video_cursor_setter(unsigned int position);
// ^^^ LOCAL FUNCTIONS ^^^

// VARIABLES
static tSystemVideo * video = (tSystemVideo *) VIDEO_DIR;
static int cursor = 0;
static int cursor_shown = TRUE;
// ^^^ VARIABLES ^^^

void video_init() {
	cursor_shown = TRUE;
	video_cursor_shape(SYSTEM_VIDEO_CURSOR_SHAPE_SQUARE);
	video_clear();
}

void video_clear() {
	int i;
	
	for(i = 0; i < SYSTEM_VIDEO_SIZE; i++) {
		video[i].character = ' ';
		video[i].style = STYLE_DEFAULT;
	}

	video_cursor_put(0);
}

void video_cursor_show(int boolean) {
	if(boolean) {
		cursor_shown = TRUE;
		video_cursor_put(cursor);
	} else {
		cursor_shown = FALSE;
		video_cursor_setter(SYSTEM_VIDEO_SIZE);
	}
}

int video_cursor_put(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}
	
	cursor = position;

	if(cursor_shown) {
		video_cursor_setter(cursor);
	}

	return OK;
}

int video_cursor_get() {
	return cursor;
}

void video_cursor_setter(unsigned int position) {
	_port_write_byte(PORT_VIDEO_INDEX, INDEX_CURSOR_LOCATION_HIGH_REGISTER);
	_port_write_byte(PORT_VIDEO_DATA, WORD_FIRST_HALF(cursor) >> 8); // High part
	_port_write_byte(PORT_VIDEO_INDEX, INDEX_CURSOR_LOCATION_LOW_REGISTER);
	_port_write_byte(PORT_VIDEO_DATA, WORD_LAST_HALF(cursor)); // Low part
}

int video_cursor_shape(tSysVideoCursorShape shape) {
	uint8_t start, end;

	switch(shape) {
		case SYSTEM_VIDEO_CURSOR_SHAPE_SQUARE:
			start = CURSOR_SHAPE_SQUARE_START;
			end = CURSOR_SHAPE_SQUARE_END;
			break;
		case SYSTEM_VIDEO_CURSOR_SHAPE_UNDERSCORE:
			start = CURSOR_SHAPE_UNDERSCORE_START;
			end = CURSOR_SHAPE_UNDERSCORE_END;
			break;
		case SYSTEM_VIDEO_CURSOR_SHAPE_DOT:
			start = CURSOR_SHAPE_DOT_START;
			end = CURSOR_SHAPE_DOT_END;
			break;
		default:
			return SYSTEM_ERROR_VIDEO_SHAPE_INVALID;
	}

	video_cursor_shape_changer(start, end);

	return OK;
}

void video_cursor_shape_changer(uint8_t start, uint8_t end) {
	// -------------------------------------------------------------------------------
	// If Cursor Scan Line End < Cursor Scan Line Start, cursor will not be displayed!
	// -------------------------------------------------------------------------------
	_port_write_byte(PORT_VIDEO_INDEX, INDEX_CURSOR_START_REGISTER);
	_port_write_byte(PORT_VIDEO_DATA, BYTE_LAST_5BITS(start)); // Top most line
	_port_write_byte(PORT_VIDEO_INDEX, INDEX_CURSOR_END_REGISTER);
	_port_write_byte(PORT_VIDEO_DATA, BYTE_LAST_5BITS(end)); // Bottom most line
}

int video_put(unsigned int position, char character) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	video[position].character = character;

	return OK;
}

int video_putWithStyle(unsigned int position, char character, tSysVideoStyle style) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	video[position].character = character;
	video[position].style = style;

	return OK;
}

char video_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return video[position].character;
}

int video_style_put(unsigned int position, tSysVideoStyle style) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	video[position].style = style;

	return OK;
}

int video_style_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return video[position].style;
}

int video_color_put(unsigned int position, tSysVideoStyle color) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	tSysVideoStyle style = video_style_get(position);
	video_style_put(position, BYTE_FIRST_HALF(style) +  BYTE_LAST_HALF(color));

	return OK;
}

int video_color_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return BYTE_LAST_HALF(video_style_get(position));
}

int video_bg_put(unsigned int position, tSysVideoStyle bg) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	tSysVideoStyle style = video_style_get(position);
	video_style_put(position, BYTE_LAST_HALF(style) +  COLOR_TO_BG(BYTE_LAST_HALF(bg)));

	return OK;
}

int video_bg_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return BG_TO_COLOR(BYTE_FIRST_HALF(video_style_get(position)));
}
