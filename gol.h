#ifndef TETRIS_H
#define TETRIS_H
#include <stdbool.h>

#ifdef __ARDUINO_TETRIS__
#include "arduino_display.h"
#include "Arduino.h"
#endif

#ifndef __ARDUINO_TETRIS__
#include "sdl_display.h"
#endif

Uint8 getPixel(Uint8 x, Uint8 y);
void setPixel(Uint8 x, Uint8 y, Uint8 value);
void setPixelP(Uint8 x, Uint8 y, Uint8 value, Uint8 *vgaxfbp);
void backupToSecondaryBuffer(Uint8 y);
//int isPixelAlive(char x, char y);

void handleEvents();
void update();
bool running(); 
void render();
void clean();
bool checkColision(int cnt_y_local);
void initTetris();
void mainGameLoop();

extern Uint8 vgaxfb[X_BYTE_SIZE * Y_SIZE];
extern Uint8 vgax_sec_buf[X_BYTE_SIZE * 3];
#endif
