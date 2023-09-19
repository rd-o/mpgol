#ifndef __ARDUINO_TETRIS__
#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "constants.h"
#include <stdbool.h>
//#include <stdint.h>

//typedef uint32_t Uint32;

extern bool isRunning;
extern int pixelSize;
struct PixelLoc {
	int x;
	int y;
};

int initDisplay(const char* title, int width, int height, bool fullscreen);
void delayMs(Uint32 ms);
void playEScore();
void playERotate();
void playEPiecesDown();
Uint32 getTicks();
void handlePlatformEvents(void (*onLeftKey)(),
		void (*onRightKey)(),
		void (*onUpKey)(),
		void (*onDownKey)(),
		void (*onSpaceKey)());
void renderPixels(struct PixelLoc pixelLoc);
void renderGraphicNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits);
void renderClear();
void cleanDisplay();
void renderBackground();
void renderPresent();

extern SDL_Window *window;
extern SDL_Renderer *renderer;


#endif
#endif

