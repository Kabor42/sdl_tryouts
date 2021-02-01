#ifndef __DOMI_MY_SDL_HELPER_H__
#define __DOMI_MY_SDL_HELPER_H__

#include "my_sdl_helper_ltimer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
/** Domi's custom class for starting up SDL */

typedef struct sSDL SDL;

/** Domi's custom class for starting up SDL */
struct sSDL {
  const uint16_t SCREEN_WIDHT = 640;
  const uint16_t SCREEN_HEIGHT = 480;

  /** Starts up SDL and creates main window */
  bool (*init)(SDL *);

  /** Loads media files */
  bool (*loadMedia)(SDL *);

  /** Frees media and shuts down SDL; */
  void (*close)(SDL *);

  /** Draw some stuff to test */
  void (*testDrawing)(SDL *);

  SDL_Texture *(*loadTexture)(SDL *, std::string path);
  SDL_Window *gWindow = NULL;
  SDL_Renderer *gRenderer = NULL;
  LTimer timer;
};

void sSDL_init_struct(SDL *s);

#endif