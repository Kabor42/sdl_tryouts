OBJS = 02_rendering_SDL.cpp

CC = g++

CFLAGS = -Wall -Werror -std=c++14 -pedantic
LDFLAGS = -lSDL2 -lSDL2_image
OBJ_NAME = 02

all: $(OBJ_NAME)


run: $(OBJ_NAME)
	./$<

$(OBJ_NAME): $(OBJS) drawing.o helper.o ltimer.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

drawing.o: my_sdl_graph.cpp helper.o
	$(CC) $(CFLAGS) -c $< -o $@

helper.o : my_sdl_helper.cpp my_sdl_helper.h ltimer.o
	$(CC) $(CFLAGS) -c $< -o $@

ltimer.o : my_sdl_helper_ltimer.cpp my_sdl_helper_ltimer.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o a.out $(OBJ_NAME)