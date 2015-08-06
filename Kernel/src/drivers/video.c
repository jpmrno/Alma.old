#include <video.h>

#define VIDEO_DIR 0xB8000
#define LAST_VIDEO_POSITION (VIDEO_SIZE - 2)
#define IS_CURSOR_AT_LAST_ROW(cursor)	\
						((cursor) / (VIDEO_COLUMNS * 2) == (VIDEO_ROWS - 1))
#define IS_CURSOR_AT_THE_BEGGINING_OF_A_LINE(cursor)	\
										(!((cursor) % (VIDEO_COLUMNS * 2)))

static char * video = (char *) VIDEO_DIR;
static int cursor = 0;
static uint8_t style = BACKGROUND_DEFAULT + COLOR_DEFAULT;

// Just for video driver
void _cursor_enable();
void _cursor_set(unsigned int position);

/**
 * Sends each row of the current screen one above
 * so as to free the last row of the screen 
 */
static void shiftUp();

/**
 * Refresh the cursor position.
 * This function should be called after every change made on video.
 */
static void updateCursor();


static void shiftUp() {
	int i, j;

	// Moves each row to the previous, the first one disappears
	for(i = 1; i < VIDEO_ROWS; i++) {
		for(j = 0; j < VIDEO_COLUMNS; j++) {
			video[((i - 1) * VIDEO_COLUMNS + j) * 2] = video[(i * VIDEO_COLUMNS + j) * 2];
			video[((i - 1) * VIDEO_COLUMNS + j) * 2 + 1] = video[(i * VIDEO_COLUMNS + j) * 2 + 1];
		}
	}

	// Cleans last row
	for(j = 0; j < VIDEO_COLUMNS; j++) {
		video[((VIDEO_ROWS - 1) * VIDEO_COLUMNS + j) * 2] = ' ';
		video[((VIDEO_ROWS - 1) * VIDEO_COLUMNS + j) * 2 + 1] = style;
	}

	// Update cursor position
	cursor -= VIDEO_COLUMNS * 2;
	updateCursor();
}

static void updateCursor() {
	_cursor_set(cursor / 2);
}


void initVideo() {
	clearAll();
	cursor = 0;
	updateCursor();
	_cursor_enable();
}


void write(char character) {
	// If cursor is in last position -> shifts up the page
	if(cursor == LAST_VIDEO_POSITION) {
		shiftUp();
	}

	video[cursor++] = character;
	video[cursor++] = style;
	updateCursor();
}


int put(char character, unsigned int position) {
	if(position >= (VIDEO_ROWS * VIDEO_COLUMNS)) {
		return ERROR_POSITION_INVALID;
	}

	video[position * 2] = character;

	return OK;
}


int putStyleOf(uint8_t thisStyle, unsigned int position) {
	if(position >= (VIDEO_ROWS * VIDEO_COLUMNS)) {
		return ERROR_POSITION_INVALID;
	}

	video[position * 2 + 1] = thisStyle;

	return OK;
}


uint8_t get(unsigned int position) {
	if(position >= (VIDEO_ROWS * VIDEO_COLUMNS)) {
		return ERROR_POSITION_INVALID;
	}
	
	return video[position * 2];
}


uint8_t getStyleOf(unsigned int position) {
	if(position >= (VIDEO_ROWS * VIDEO_COLUMNS)) {
		return ERROR_POSITION_INVALID;
	}
	
	return video[position * 2 + 1];
}


int setCursor(unsigned int position) {
	if(position >= (VIDEO_ROWS * VIDEO_COLUMNS * 2)) {
		return ERROR_POSITION_INVALID;
	}
	
	cursor = position;
	updateCursor();
	return OK;
}


unsigned int getCursor() {
	return cursor;
}


void newLine() {
	// If cursor is in last row: shift up the page
	if(IS_CURSOR_AT_LAST_ROW(cursor)) {
		shiftUp();
	}

	/*
	 *	If cursor is at the beginning of a line, it inserts a blank space
	 *	to be able to use the next while cylce
	 */ 
	if(IS_CURSOR_AT_THE_BEGGINING_OF_A_LINE(cursor)) {
		video[cursor++] = ' ';
		video[cursor++] = style;
	}

	while(!IS_CURSOR_AT_THE_BEGGINING_OF_A_LINE(cursor)) {
		video[cursor++] = ' ';
		video[cursor++] = style;
	}

	updateCursor();
}

void delete() {
	if(cursor != 0) {
		video[--cursor] = style;
		video[--cursor] = ' ';
		updateCursor();
	}
}


void clearAll() {
	int i;

	cursor = 0;

	for(i = 0; i < (VIDEO_ROWS * VIDEO_COLUMNS * 2); i += 2) {
		video[i] = ' ';
		video[i + 1] = style;
	}

	updateCursor();
}


void clearStyle() {
	styleAll(BACKGROUND_DEFAULT + COLOR_DEFAULT);
}


void styleAll(uint8_t newStyle) {
	int i, j;

	for(i = 0; i < VIDEO_ROWS; i++) {
		for(j = 0; j < VIDEO_COLUMNS; j++) {
			video[(i * VIDEO_COLUMNS + j) * 2 + 1] = newStyle;
		}
	}

	style = newStyle;
}


void colorAll(uint8_t color) {
	styleAll((style & 0xF0) + color);
}


void backgroundAll(uint8_t background) {
	styleAll((style & 0x0F) + background);
}


void restoreStyle() {
	setStyle(BACKGROUND_DEFAULT + COLOR_DEFAULT);
}


void setStyle(uint8_t newStyle) {
	style = newStyle;
}


uint8_t getStyle() {
	return style;
}


void setColor(uint8_t color) {
	style = (style & 0xF0) + color;
}


void setBackground(uint8_t background) {
	style = (style & 0x0F) + background;
}
