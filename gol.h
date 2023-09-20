#ifndef GOL_H
#define GOL_H
#include <stdbool.h>

#ifdef ARDUINO
#include "arduino_display.h"
#include "Arduino.h"

typedef byte Uint8;
typedef int Uint16;
#endif

#ifndef ARDUINO
#include "sdl_display.h"
#endif

Uint8 getPixel(Uint8 x, Uint8 y);
void setPixel(Uint8 x, Uint8 y, Uint8 value);
void backupToSecondaryBuffer(Uint8 y);
void nextGeneration();

void handleEvents();
void update();
bool running(); 
void render();
void clean();
bool checkColision(int cnt_y_local);
void initTetris();
void mainGameLoop();

#endif
