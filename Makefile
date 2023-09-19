#OBJS specifies which files to compile as part of the project
OBJS = main.c sdl_display.c gol.cpp
TEST = test.c sdl_display.c gol.cpp

#CC specifies which compiler we're using
CC = g++

EMCC = /usr/lib/emscripten/emcc
TITLE=gol
EXEC_FILE=gol
#FLAGS=-Wall -Wextra -std=c99

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lm

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = $(TITLE)

#This is the target that compiles our executable
#all : $(OBJS)
#	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: $(EXEC_FILE)

OBJECTS_C=main.o sdl_display.o
OBJECTS_CPP=gol.o
DEPS=sdl_display.h gol.h

$(EXEC_FILE): $(OBJECTS_C) $(OBJECTS_CPP)
	$(CC) $^ $(LINKER_FLAGS) -o $@

$(OBJECTS_C): %.o: %.c
	$(CC) $< $(COMPILER_FLAGS) -c -o $@

$(OBJECTS_CPP): %.o: %.cpp
	$(CC) $< $(COMPILER_FLAGS) -c -o $@



#$(EXEC_FILE): 

wasm : $(OBJS)
	mkdir -p wasm_out
	$(EMCC) -O3 --closure 1 -s USE_SDL=2 -lSDL -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_MIXER=2 -s SDL2_MIXER_FORMATS='["wav"]' -s ALLOW_MEMORY_GROWTH=1 -s WASM=2 --preload-file assets $(FLAGS) $(OBJS) -o wasm_out/$(TITLE).html
#	$(EMCC) --shell-file html/tetris_minimal.html -O3 --closure 1 -s USE_SDL=2 -lSDL -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_MIXER=2 -s SDL2_MIXER_FORMATS='["wav"]' -s ALLOW_MEMORY_GROWTH=1 -s WASM=2 --preload-file assets $(FLAGS) $(OBJS) -o wasm_out/$(TITLE).html

run-wasm:
	python3 -m http.server

clean:
	rm *.o $(EXEC_FILE)
