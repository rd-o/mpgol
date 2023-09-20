#ifndef ARDUINO_DISPLAY_H
#define ARDUINO_DISPLAY_H
#include "constants.h"
#include "Arduino.h"


typedef unsigned long Uint32;

extern bool isRunning;
extern int pixelSize;

int initDisplay(const char* title, int width, int height, bool fullscreen);
void delayMs(Uint32 ms);
void playEScore();
void playERotate();
void playEPiecesDown();
void cleanDisplay();

void renderPixels(struct PixelLoc pixelLoc);
void renderGraphicNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits);
void renderClear();
void renderBackground();
void renderPresent();
Uint32 getTicks();
void handlePlatformEvents(void (*onLeftKey)(),
		void (*onRightKey)(),
		void (*onUpKey)(),
		void (*onDownKey)(),
		void (*onSpaceKey)());



struct PixelLoc {
	int x;
	int y;
};

#endif

