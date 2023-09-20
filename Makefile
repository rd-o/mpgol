CC = g++

EXEC_FILE=gol

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lm

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

clean:
	rm *.o $(EXEC_FILE)

