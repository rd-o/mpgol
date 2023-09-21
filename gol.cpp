#include "gol.h"
#include <stdlib.h>
#include <math.h>

#ifndef ARDUINO
Uint8 vgaxfb[X_BYTE_SIZE * Y_SIZE];
#else
#include <VGAX.h>
VGAX vga;
#endif

//only use 3 lines
Uint8 vgax_sec_buf[X_BYTE_SIZE * 4];

void mainGameLoop(){
	//handleEvents();
	render();
	update();
}


void initTetris()
{
  if(initDisplay("Game of Life", 980, 700, false) == 1)
  {
          return;
  }
  #ifdef ARDUINO
  vga.begin();
  vga.clear(0);
  #else
  for(int i = 0; i < X_BYTE_SIZE * Y_SIZE; i++) {
    vgaxfb[i] = 0;
  }
  #endif

  //two gliders
  setPixel(2, 0, 3);
  setPixel(3, 1, 3);
  setPixel(1, 2, 3);
  setPixel(2, 2, 3);
  setPixel(3, 2, 3);

  setPixel(117, 59, 3);
  setPixel(118, 59, 3);
  setPixel(119, 59, 3);
  setPixel(119, 58, 3);
  setPixel(118, 57, 3);
}

void onLeftKey()
{
}

void onRightKey()
{
}

void onUpKey()
{
  nextGeneration();
}

void onDownKey()
{
}

void onSpaceKey()
{
  initTetris();
}

void handleEvents()
{
  handlePlatformEvents(&onLeftKey, &onRightKey, &onUpKey, &onDownKey, &onSpaceKey);
}

int toroidCalcX(char value) {
  if(value == -1) {
    return X_SIZE - 1;
  } else if(value == X_SIZE) {
    return 0;
  } else {
    return value;
  }
}

int isPixelAlive(char x, char y1) {
  Uint8 xAdapted = toroidCalcX(x);
  Uint8 twoBitPos = 6 - (x & 3) * 2;

  return ((vgax_sec_buf[(int) xAdapted / 4 + y1 * X_BYTE_SIZE] >> twoBitPos) & 0b11) == 3;
}

Uint8 getNeighbors(char x, char y) {

  Uint8 neighbors = 0;

  if (isPixelAlive (x-1, 0)) neighbors++;
  if (isPixelAlive (x, 0)) neighbors++;
  if (isPixelAlive (x+1, 0)) neighbors++;
  if (isPixelAlive (x-1, 1)) neighbors++;
  if (isPixelAlive (x+1, 1)) neighbors++;
  if (isPixelAlive (x-1, 2)) neighbors++;
  if (isPixelAlive (x, 2)) neighbors++;
  if (isPixelAlive (x+1, 2)) neighbors++;

  return neighbors;
}

Uint8 getPixelSec(Uint8 x, Uint8 y) {
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE;
  Uint8 twoBitPos = 6 - (x - (4 * ((int) x / 4))) * 2;
  return (vgax_sec_buf[arrayNumber] >> twoBitPos) & 0b11;
}


#ifndef ARDUINO
void printVgaSecBuf() {
  printf("-------------> \n");
  for(int j = 0; j < 4; j++) {
    for(int i = 0; i < X_SIZE; i++) {
      if(getPixelSec(i, j) == 3) {
        printf("#");
      }else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
#endif

void firstBackupToSecondaryBuffer() {
  int y_tmp;
  for(int j = 0; j < 3; j++)
    for(int i = 0; i < X_BYTE_SIZE; i++) {
      if (j == 0) {
        y_tmp = Y_SIZE - 1;
      } else {
        y_tmp = j - 1;
      }
      
      vgax_sec_buf[i + X_BYTE_SIZE * j] = vgaxfb[i + X_BYTE_SIZE * y_tmp];
    }

  //backup of the first line to allow calculations with the last y line
  for(int i = 0; i < X_BYTE_SIZE; i++) {
    vgax_sec_buf[i + X_BYTE_SIZE * 3] = vgaxfb[i];
  }
}

void backupToSecondaryBuffer(Uint8 y) {
  Uint8 lastBackup = 0;
  if(y == Y_SIZE - 1) {
    lastBackup = 1;
  }

  for(int j = 0; j < 3; j++)
    for(int i = 0; i < X_BYTE_SIZE; i++) {
      if(j == 2) {
        if(!lastBackup) {
          vgax_sec_buf[i + X_BYTE_SIZE * j] = vgaxfb[i + X_BYTE_SIZE * (j - 1 + y)];
        } else {
          //see firstBackupToSecondaryBuffer
          vgax_sec_buf[i + X_BYTE_SIZE * j] = vgax_sec_buf[i + X_BYTE_SIZE * 3];
        }
      } else {
        vgax_sec_buf[i + X_BYTE_SIZE * j] = vgax_sec_buf[i + X_BYTE_SIZE * (j + 1)];
      }
    }
}

void nextGeneration() {
  Uint8 neighbors;

  firstBackupToSecondaryBuffer();
#ifndef ARDUINO
  //printVgaSecBuf();
#endif

  for (char y = 0; y <= Y_SIZE - 1; y++) {
    for (char x = 0; x < X_SIZE; x++) {
      neighbors = getNeighbors(x, y);

      if (isPixelAlive (x, 1))
      {
        // Pixel is alive; remains alive with 2 or 3 neighbors.
        if ((neighbors == 2) || (neighbors == 3)){
          //setPixel(x, y, 3);
        }
        else {
          setPixel(x, y, 0);
        }
      }
      else
      {
        // Cell is dead; new cell is born when it has exactly 3 neighbors.
        if (neighbors == 3) {
          setPixel(x, y, 3);
        }
        else {
          //setPixel(x, y, 0);
        }
      }
    }

    //if(y + 1 <= Y_SIZE - 2) {
      backupToSecondaryBuffer(y + 1);
    //}
    #ifndef ARDUINO
    //printVgaSecBuf();
    #endif
  }
}

void update()
{
  nextGeneration();
  delayMs(50);
}


void renderNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits)
{
	renderGraphicNumbers(value, numberPosX, numberPosY, numberOfDigits);
}

//returns two bit value for pixel
Uint8 getPixel(Uint8 x, Uint8 y) {
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE;
  Uint8 twoBitPos = 6 - (x & 3) * 2;
  return (vgaxfb[arrayNumber] >> twoBitPos) & 0b11;
}

void setPixel(Uint8 x, Uint8 y, Uint8 value) {
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE ;
  Uint8 twoBitPos = 6 - (x & 3) * 2;
  vgaxfb[arrayNumber] &= ~(0b11 << twoBitPos);
  vgaxfb[arrayNumber] |= value << twoBitPos;
}

void renderBuffer()
{
  struct PixelLoc pixelLoc;
  for(int i = 0; i < X_SIZE; i++)
    for(int j = 0; j < Y_SIZE; j++)
    {
      if(getPixel(i, j) == 3) {
        pixelLoc.x = i * pixelSize + SCREEN_FACTOR;
        pixelLoc.y = j * pixelSize + SCREEN_FACTOR;
        renderPixels(pixelLoc);
      }
    }
}

void render()
{
	struct PixelLoc pixelLoc;
	renderClear();
	
	//renderBackground();
	
	//renderNumbers(score, SCORE_NUMBER_POS_X, SCORE_NUMBER_POS_Y, SCORE_DIGITS);
	//renderNumbers(level, LEVEL_NUMBER_POS_X, LEVEL_NUMBER_POS_Y, LEVEL_DIGITS);
	//renderNumbers(lineCounter, LINES_NUMBER_POS_X, LINES_NUMBER_POS_Y, LINES_DIGITS);
	//renderNextPiece();
        renderBuffer();

	//renderMovingPiece();

        /*
	int i,j;
	for(i = 0; i < X_SIZE; i++)
		for(j = 0; j < Y_SIZE; j++)
			if(tm[i][j])
			{
				pixelLoc.x = i * pixelSize + screenPosX;
				pixelLoc.y = j * pixelSize + screenPosY;
				renderPixels(pixelLoc);
			}
                        */

	renderPresent();
}

void clean()
{
	cleanDisplay();
}

bool running()
{
	return isRunning;
}
