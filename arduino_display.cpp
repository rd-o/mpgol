#include "arduino_display.h"

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);

int pixelSize = SCREEN_FACTOR * PIXEL_ORIGINAL_SIZE;

bool loadMedia()
{
	return false;
}

int initDisplay(const char* title, int width, int height, bool fullscreen)
{
  /*
	display.begin();
	display.setContrast(75);
        */
	return 0;
}

void delayMs(Uint32 ms)
{
}

void playEScore()
{
}

void playERotate()
{
}

void playEPiecesDown()
{
}

void drawPixel(int x, int y)
{
	//display.fillRect(y, 47 - x -3, 3, 3, 1);
}

void renderPixels(struct PixelLoc pixelLoc)
{
	//drawPixel(pixelLoc.x, pixelLoc.y);
}

void renderGraphicNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits)
{
}

void renderClear()
{
	//display.clearDisplay();
}

void renderBackground()
{
}

void renderPresent()
{
	//display.display();
}

void handlePlatformEvents(void (*onLeftKey)(),
		void (*onRightKey)(),
		void (*onUpKey)(),
		void (*onDownKey)(),
		void (*onSpaceKey)())
{
	if(digitalRead(6) == HIGH)
	{
		(*onUpKey)();
	}

	if(digitalRead(8) == HIGH)
	{
		(*onDownKey)();
	}

	if(digitalRead(7) == HIGH)
	{
		(*onLeftKey)();
	}

	if(digitalRead(9) == HIGH)
	{
		(*onRightKey)();
	}
}

Uint32 getTicks()
{
	return millis();
}

void cleanDisplay()
{
}

