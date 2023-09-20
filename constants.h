#ifndef CONSTANTS_H
#define CONSTANTS_H


#define WINDOW_W 1
#define WINDOW_H 1
#define PIECE_DELAY 400
#define SCORE_NUMBER_POS_X 109
#define SCORE_NUMBER_POS_Y 27
#define LEVEL_NUMBER_POS_X 127
#define LEVEL_NUMBER_POS_Y 50
#define LINES_NUMBER_POS_X 109
#define LINES_NUMBER_POS_Y 72
#define SCORE_DIGITS 5
#define LEVEL_DIGITS 2
#define LINES_DIGITS 5
#define FPS 60

#ifdef ARDUINO
#define SCREEN_FACTOR 1
#define PIXEL_ORIGINAL_SIZE 3
#define SCREEN_POS_X 0
#define SCREEN_POS_Y 0

#define X_SIZE 120
#define Y_SIZE 60
#define X_BYTE_SIZE 30
#endif

#ifndef ARDUINO
#define SCREEN_FACTOR 1
#define PIXEL_ORIGINAL_SIZE 8
#define SCREEN_POS_X 11
#define SCREEN_POS_Y 0

#define VGAX_HEIGHT 60 //number of lines
#define VGAX_BWIDTH 30 //number of bytes in a row

#define X_SIZE 120
#define Y_SIZE 60
#define X_BYTE_SIZE 30
#endif

#endif
