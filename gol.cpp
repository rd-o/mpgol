#include "gol.h"
#include <stdlib.h>
#include <math.h>

int levelDelay[] = {887, 820, 753, 686, 619, 552, 469, 368, 285, 184, 167, 
	151, 134, 117, 100, 100, 84, 84, 67, 67, 50};
int pointsForLine[] = {40, 100,	300, 1200};
int level = 20;
int lineCounter;
int lineCounterForLevel;

Uint32 pieceCnt = 0;
//int tm[X_SIZE][Y_SIZE];

#ifndef __ARDUINO_TETRIS__
Uint8 vgaxfb[X_BYTE_SIZE * Y_SIZE];
#endif
//only use 3 lines
Uint8 vgax_sec_buf[X_BYTE_SIZE * 3];

static int screenPosX = SCREEN_POS_X * SCREEN_FACTOR;
static int screenPosY = SCREEN_POS_Y * SCREEN_FACTOR;

int cnt_y  = 0;
int cnt_x  = 5;
int posMovingPieceX;
int posMovingPieceY;
int score;
bool afterReset;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

void mainGameLoop(){
	Uint32 frameStart;
	int frameTime;

	frameStart = getTicks();

	//handleEvents();
	render();
	update();

	frameTime = getTicks() - frameStart;

	if(frameDelay > frameTime)
	{
		delayMs(frameDelay - frameTime);
	}
}


void initTetris()
{
	int i, j;
	pieceCnt = getTicks();
	if(initDisplay("Game of Life", 160 * 4, 144 * 4, false) == 1)
	{
		return;
	}

  for(int i = 0; i < X_BYTE_SIZE * Y_SIZE; i++) {
    vgaxfb[i] = 0;
  }

  /*
  for(int j = 0; j < Y_SIZE; j++)
    for(int i = 0; i < X_SIZE; i++) {
      setPixel(i, j, 3);
    }
*/
  /*for(int i = 0; i < X_SIZE * Y_SIZE; i++) {
    printf("vgaxfb[%i]: %i\n", i, vgaxfb[i]);
  }*/

  setPixel(1, 0, 3);
  setPixel(2, 1, 3);
  setPixel(0, 2, 3);
  setPixel(1, 2, 3);
  setPixel(2, 2, 3);
  /*
  setPixel(0, 0, 3);
  setPixel(1, 0, 3);
  setPixel(2, 0, 3);
  setPixel(3, 0, 3);
  setPixel(4, 0, 3);
  setPixel(5, 0, 3);
  setPixel(6, 0, 3);
  setPixel(7, 0, 3);
  */
  printf("vgaxfb[%i]: %i\n", 0, vgaxfb[0]);
}

void onLeftKey()
{
}

void onRightKey()
{
}

void onUpKey()
{
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

/*
int isPixelAlive(char x, char y, char x1, char y1) {
  printf("isPixelAlive -->: (%i, %i)\n", x, y);
  Uint8 xAdapted = toroidCalcX(x);
  Uint8 yAdapted = toroidCalcY(y);

  Uint16 arrayNumber = (int) xAdapted / 4 + yAdapted * X_BYTE_SIZE;

  Uint8 twoBitPos = 6 - (xAdapted - (4 * ((int) xAdapted / 4))) * 2;

  //printf("isPixelAlive, xAdapted, yAdapted, arrayNumber, twoBitPos (%i, %i, %i, %i)\n", xAdapted, yAdapted, arrayNumber, twoBitPos);

  if(yAdapted == (Y_SIZE - 1)) {
    return ((vgaxfb[arrayNumber] >> twoBitPos) & 0b11) == 3;
  } else {
    printf("\n isPixelAlive: vgax_sec_buf[%i]: %i\n", arrayNumber, vgax_sec_buf[arrayNumber] );
    return ((vgax_sec_buf[(int) x1 / 4 + y1 * X_BYTE_SIZE] >> twoBitPos) & 0b11) == 3;
  }
}
*/
int toroidCalcX(char value) {
  if(value == -1) {
    return X_SIZE - 1;
  } else if(value == X_SIZE) {
    return 0;
  } else {
    return value;
  }
}

int toroidCalcY(char value) {
  if(value == -1) {
    return Y_SIZE - 1;
  } else if(value == Y_SIZE) {
    return 0;
  } else {
    return value;
  }
}

/*
int isPixelAlive(char x, char y, char x1, char y1) {
  Uint8 xAdapted = toroidCalcX(x);
  Uint8 twoBitPos = 6 - (x - (4 * ((int) x / 4))) * 2;

  return ((vgax_sec_buf[(int) xAdapted / 4 + y1 * X_BYTE_SIZE] >> twoBitPos) & 0b11) == 3;
}
*/

int isPixelAlive(char x, char y1) {
  Uint8 xAdapted = toroidCalcX(x);
  Uint8 twoBitPos = 6 - (x - (4 * ((int) x / 4))) * 2;

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

void printVgaSecBuf() {
  printf("-------------> \n");
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < X_BYTE_SIZE; i++) {
      if(getPixelSec(i, j) == 3) {
        printf("#");
      }else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

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
      
      //printf("(%i, %i), y_tmp: %i, vgax_sec_buf[%i], vgaxfb[%i] = %i \n", 
      //    i, j, y_tmp, i + X_BYTE_SIZE * j, i + X_BYTE_SIZE * y_tmp, vgaxfb[i + X_BYTE_SIZE * y_tmp]);
    }
}

void backupToSecondaryBuffer(Uint8 y) {
  for(int j = 0; j < 3; j++)
    for(int i = 0; i < X_BYTE_SIZE; i++) {

      if(j == 2) {
        vgax_sec_buf[i + X_BYTE_SIZE * j] = vgaxfb[i + X_BYTE_SIZE * (j - 1 + y)];
      } else {
        vgax_sec_buf[i + X_BYTE_SIZE * j] = vgax_sec_buf[i + X_BYTE_SIZE * (j + 1)];
      }

      //printf("(%i, %i), vgax_sec_buf[%i], vgaxfb[%i] = %i \n", 
      //    i, j, i + X_BYTE_SIZE * j, i + X_BYTE_SIZE * y_tmp, vgaxfb[i + X_BYTE_SIZE * y_tmp]);
    }
}

void nextGeneration() {
  Uint8 neighbors;

  firstBackupToSecondaryBuffer();
  printVgaSecBuf();

  for (char y = 0; y < Y_SIZE; y++) {
    for (char x = 0; x < X_SIZE; x++) {
      neighbors = getNeighbors(x, y);

      printf("(%i, %i) ne: %i - ", x, y, neighbors);
      
      if(getPixel(x, y) == 3) {
        printf(" alive ");
      } else {
        printf(" death ");
      }

      if (isPixelAlive (x, 1))
      {
        // Pixel is alive; remains alive with 2 or 3 neighbors.
        if ((neighbors == 2) || (neighbors == 3)){
          setPixel(x, y, 3);
          printf("- alive\n");
        }
        else {
          setPixel(x, y, 0);
          printf("- death\n");
        }
      }
      else
      {
        // Cell is dead; new cell is born when it has exactly 3 neighbors.
        if (neighbors == 3) {
          setPixel(x, y, 3);
          printf("- alive\n");
        }
        else {
          setPixel(x, y, 0);
          printf("- death\n");
        }
      }
    }
    backupToSecondaryBuffer(y + 1);
    printVgaSecBuf();
  }
}

void update()
{
  //scoring();
  Uint32 currentPieceCnt = getTicks();
  if((currentPieceCnt - pieceCnt) > levelDelay[level])
  {
    printf("call next\n");
    nextGeneration();
    pieceCnt = currentPieceCnt;
  }
}


void renderNumbers(int value, int numberPosX, int numberPosY, int numberOfDigits)
{
	renderGraphicNumbers(value, numberPosX, numberPosY, numberOfDigits);
}

void renderNextPiece()
{
  /*
	struct PixelLoc pixelLoc;
	int i,j;
	for(i = 0; i < PIECE_H; i++)
		for(j = 0; j < PIECE_H; j++)
			if(nextPiece[j][i])
			{
				pixelLoc.x = pixelSize * j + 109 * SCREEN_FACTOR;
				pixelLoc.y = pixelSize * i + 93 * SCREEN_FACTOR;
				renderPixels(pixelLoc);
			}
                        */
	struct PixelLoc pixelLoc;
        int i = 0, j = 0;
	pixelLoc.x = pixelSize * j + 109 * SCREEN_FACTOR;
	pixelLoc.y = pixelSize * i + 93 * SCREEN_FACTOR;
	renderPixels(pixelLoc);
}

Uint8 getTwoBitPos(Uint8 x) {
  return 6 - (x - (4 * ((int) x / 4))) * 2;
}


//returns two bit value for pixel
Uint8 getPixel(Uint8 x, Uint8 y) {
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE;
  //printf("(%i, %i)", x, y);
  //printf("vgaxfb[%i]: %i", arrayNumber, vgaxfb[arrayNumber]);

  Uint8 twoBitPos = 6 - (x - (4 * ((int) x / 4))) * 2;

  //printf("twoBitPos: %i ", twoBitPos);
  //int res = (vgaxfb[arrayNumber] >> twoBitPos) & 0b11;

  //printf(" = %i\n", res);
  //return res;
  return (vgaxfb[arrayNumber] >> twoBitPos) & 0b11;
  ////return (vgaxfb[arrayNumber] >> 6 - x * 2) & 0b11;
}
/*
void setPixel(Uint8 x, Uint8 y, Uint8 value) {
  printf("x: %i, y: %i\n", x, y);
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE ;
  printf("arrayNumber: %i \n", arrayNumber);
  Uint8 twoBitPos = (x - (4 * ((int) x / 4))) * 2;
  printf("twoBitPos: %i ", twoBitPos);
  vgaxfb[arrayNumber] &= ~(0b11 << twoBitPos);
  vgaxfb[arrayNumber] |= value << twoBitPos;
  printf("vgaxfb[%i]: %i\n", arrayNumber, vgaxfb[arrayNumber]);
}
*/

void setPixel(Uint8 x, Uint8 y, Uint8 value) {
  Uint16 arrayNumber = (int) x / 4 + y * X_BYTE_SIZE ;
  //Uint8 twoBitPos = (x - (4 * ((int) x / 4))) * 2;
  Uint8 twoBitPos = getTwoBitPos(x);
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
        //printf("i: %i, j: %i\n");
        //pixelLoc.x = i * pixelSize + 109 * SCREEN_FACTOR;
        //pixelLoc.y = j * pixelSize + 93 * SCREEN_FACTOR;
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
