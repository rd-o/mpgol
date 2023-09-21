# Multiplatform Game Of Life

This implementation is capable to execute Conway's Game Of Life in Arduino, Desktop and Web.
GTK is used to show graphics in Desktop and Web. For Arduino the vgax library is used.

## How to compile
### Desktop
Install GTK2 libraries and includes and execute the following commands:

    make clean
    make 

### Web
Install emscripten, check that the paths are correct in Makefile-was and then execute:

    make -f Makefile-wasm clean
    make -f Makefile-wasm 
    make -f Makefile-wasm run-wasm

Once executed go to the following URL http://localhost:8000/wasm_out/gol.html

### Arduino
Go to Arduino IDE, open mpgol.ino and then click to Upload. The code was tested in Arduino Nano with old bootloader. To build the VGA interface circuit go to https://github.com/smaffer/vgax/


