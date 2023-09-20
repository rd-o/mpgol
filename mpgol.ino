#include "gol.h"
#include <VGAX.h>

VGAX vga;


void setup() {                
  vga.begin();
  vga.clear(0);

  initTetris();
}

void loop() {
  //mainGameLoop();
  nextGeneration();
  //delay(100);
}
