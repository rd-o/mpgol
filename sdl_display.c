#ifndef ARDUINO
#include "sdl_display.h"

bool isRunning = false;
int pixelSize = SCREEN_FACTOR * PIXEL_ORIGINAL_SIZE;

SDL_Texture* numbers;
SDL_Texture* pixels;
SDL_Texture* background;
SDL_Rect srcR, destR, staticPixel, backgroundRect;
SDL_Rect pixelRect, pixelTextureRect;
SDL_Window *window;
SDL_Renderer *renderer;
//sound effects
Mix_Chunk *ePiecesDown = NULL;
Mix_Chunk *eRotate = NULL;
Mix_Chunk *eScore = NULL;

bool loadMedia()
{
	bool success = true;

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}

	ePiecesDown = Mix_LoadWAV("assets/effects/ePiecesDown.wav");
	if(ePiecesDown == NULL )
	{	
        	printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	eRotate = Mix_LoadWAV("assets/effects/eRotate.wav");
	if(eRotate == NULL )
	{	
        	printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	eScore = Mix_LoadWAV("assets/effects/eScore.wav");
	if(eScore == NULL )
	{	
        	printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}

int initDisplay(const char* title, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer);
	isRunning = true;

	SDL_Surface* tmpSurface = IMG_Load("assets/textures/numbers.png");
	numbers = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("assets/textures/pixels.png");
	if(!tmpSurface) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	pixels = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load("assets/textures/background.png");
	background = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.h = 144 * 4;
	backgroundRect.w = 160 * 4;

	destR.h = pixelSize;
	destR.w = pixelSize;
	staticPixel.h = pixelSize;
	staticPixel.w = pixelSize;

	loadMedia();

	return 0;
}

void delayMs(Uint32 ms)
{
	SDL_Delay(ms);
}

void playEScore()
{
	Mix_PlayChannel(-1, eScore, 0);
}

void playERotate()
{
	Mix_PlayChannel(-1, eRotate, 0);
}

void playEPiecesDown()
{
	Mix_PlayChannel(-1, ePiecesDown, 0);
}

void renderPixels(struct PixelLoc pixelLoc)
{
	pixelTextureRect.x = 0;
	pixelTextureRect.y = 0;
	pixelTextureRect.w = 8;
	pixelTextureRect.h = 8;
	destR.x = pixelLoc.x;
	destR.y = pixelLoc.y;

	SDL_RenderCopy(renderer, pixels, &pixelTextureRect, &destR);
}

void renderGraphicNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits)
{
	SDL_Rect numberSelectorRect, numberRect;
	numberSelectorRect.w = 5;
	numberSelectorRect.h = 7;

	numberRect.w = 5 * SCREEN_FACTOR;
	numberRect.h = 7 * SCREEN_FACTOR;
	numberRect.y = numberPosY * SCREEN_FACTOR;

	int n = numberOfDigits - 1;
	int res;
	int tmpValue = value;
	while(n >= 0)
	{
		res = tmpValue / (pow(10, n));
		tmpValue = tmpValue - res * pow(10, n);
		numberSelectorRect.x = res * 5;
		numberSelectorRect.y = 0;
		numberRect.x = numberPosX * SCREEN_FACTOR + (numberOfDigits - n - 1) * 6 * SCREEN_FACTOR;
		SDL_RenderCopy(renderer, numbers, &numberSelectorRect, &numberRect);
		n--;
	}
}

void renderClear()
{
	SDL_RenderClear(renderer);
}

void renderBackground()
{
	SDL_RenderCopy(renderer, background, NULL, &backgroundRect);
}

void renderPresent()
{
	SDL_RenderPresent(renderer);
}

void handlePlatformEvents(void (*onLeftKey)(),
		void (*onRightKey)(),
		void (*onUpKey)(),
		void (*onDownKey)(),
		void (*onSpaceKey)())
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}

	if( event.type == SDL_KEYDOWN ){
		switch( event.key.keysym.sym ){
		    case SDLK_LEFT:
			(*onLeftKey)();
		    	break;
                    case SDLK_RIGHT:
			(*onRightKey)();
                    	break;
		    case SDLK_UP:
			(*onUpKey)();
			break;
		    case SDLK_DOWN:
			(*onDownKey)();
			break;
		    case SDLK_SPACE:
			(*onSpaceKey)();
			break;
		}
	}

}

Uint32 getTicks()
{
	return SDL_GetTicks();
}

void cleanDisplay()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
#endif
