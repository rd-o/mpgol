#ifndef __ARDUINO_TETRIS__
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "gol.h"

int main(int argc, char *argv[])
{
	initTetris();

	#ifdef __EMSCRIPTEN__
                emscripten_set_main_loop(mainGameLoop, 0, 1);
	#endif

	#ifndef __EMSCRIPTEN__
		while (running())
		{
			mainGameLoop();
		}
	#endif

	clean();
  /*
  vgaxfb[0] = 128;
  vgaxfb[X_BYTE_SIZE] = 64;
  vgaxfb[X_BYTE_SIZE * (Y_SIZE - 1)] = 64;
  backupToSecondaryBuffer(1);
  for(int i = 0; i < X_BYTE_SIZE * 3; i++) {
    printf("[%i] = %i\n", i, vgax_sec_buf[i]);
  }
  */
	return 0;
}
#endif
