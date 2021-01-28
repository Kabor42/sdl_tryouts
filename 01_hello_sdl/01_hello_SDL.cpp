#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc,  char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf("SDL coult not initialize!\nSDL_Error: %s\n", SDL_GetError());
  } else {
    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN );
    if ( window == NULL ) {
      printf("SDL Window could not be created!\nSDL_Error: %s\n", SDL_GetError());
    } else {
      screenSurface = SDL_GetWindowSurface( window );
      SDL_FillRect ( screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF ));
      SDL_UpdateWindowSurface( window );
      SDL_Delay(2000);
    }
  }
  SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}