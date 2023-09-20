#ifndef ARDUINO
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
	return 0;
}
#endif
