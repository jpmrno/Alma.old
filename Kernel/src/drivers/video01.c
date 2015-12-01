#include <video01.h>

// DEFINES
#define VIDEO_DIR 0xB8000

typedef struct {
    uint8_t character;
    uint8_t style;
} tSystemVideo;
// DEFINES

// ASM FUNCTIONS
void _video_cursor_set(unsigned int position); // TODO: ASM file functions rename. Static?
void _video_cursor_init(); // TODO: ASM file functions rename. Static?
// ASM FUNCTIONS
 
// LOCAL FUNCTIONS
static void video_cursor_init();
// LOCAL FUNCTIONS

// VARIABLES
static tSystemVideo * video = (tSystemVideo *) VIDEO_DIR;
static int cursor = 0;
static int cursor_shown = TRUE;
// VARIABLES

void video_init() {
	video_cursor_init();
	video_clear();
}

void video_cursor_init() {
	cursor_shown = TRUE;
	_video_cursor_init();
}

void video_clear() {
	for(i = 0; i < SYSTEM_VIDEO_SIZE; i++) {
		video[i].character = ' ';
		video[i].style = SYSTEM_VIDEO_STYLE_DEFAULT;
	}

	video_cursor_set(0);
}

void video_cursor_show(int boolean) {
	if(boolean) {
		cursor_shown = TRUE;
		video_cursor_set(cursor);
	} else {
		cursor_shown = FALSE;
		_video_cursor_set(SYSTEM_VIDEO_SIZE);
	}
}

int video_cursor_set(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}
	
	cursor = position;

	if(cursor_shown) {
		_video_cursor_set(cursor);
	}

	return OK;
}

int video_cursor_get() {
	return cursor;
}

int video_put(unsigned int position, char character) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	video[position].character = character;

	return OK;
}

int video_putWithStyle(unsigned int position, char character, vstyle_t style) {
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

	return video[position].character; // TODO: Lo puede modificar???
}

int video_style_put(unsigned int position, vstyle_t style) {
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

	return video[position].style; // TODO: Lo puede modificar???
}

int video_color_put(unsigned int position, vstyle_t color) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	style = video_style_get(position);
	video_style_put(position, (style & 0xF0) +  (color & 0x0F));
}

int video_color_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return video_style_get(position) & 0x0F;
}

int video_bg_put(unsigned int position, vstyle_t bg) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	style = video_style_get(position);
	video_style_put(position, (style & 0x0F) +  ((bg & 0x0F) << 4));
}

int video_bg_get(unsigned int position) {
	if(position >= SYSTEM_VIDEO_SIZE) {
		return SYSTEM_ERROR_VIDEO_CURSOR_INVALID;
	}

	return (video_style_get(position) & 0xF0) >> 4;
}
