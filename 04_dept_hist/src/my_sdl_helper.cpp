#include "../include/my_sdl_helper.h"

bool _init(SDL *s) {
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized!\nSDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Set tecxture filtering to linear.
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    // Create window
    s->gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, s->SCREEN_WIDHT,
                                  s->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (s->gWindow == NULL) {
      printf("Window could not be created!\n%s\n", SDL_GetError());
      success = false;
    } else {
      // Create renderer for the window.
      s->gRenderer =
          SDL_CreateRenderer(s->gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (s->gRenderer == NULL) {
        printf("Renderer coult not be created!\n%s\n", SDL_GetError());
        success = false;
      } else {
        // Initialize renderer color.
        SDL_SetRenderDrawColor(s->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading.
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_Image coult not be created!\n%s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}

bool _loadMedia(SDL *s) {
  bool success = true;

  return success;
}

void _close(SDL *s) {
  SDL_DestroyRenderer(s->gRenderer);
  SDL_DestroyWindow(s->gWindow);
  s->gWindow = NULL;
  s->gRenderer = NULL;

  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *_loadTexture(SDL *s, std::string path) {
  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image from path;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s!\nSDL_Image_Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Create texture from surface pixels;
    newTexture = SDL_CreateTextureFromSurface(s->gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s!, SDL_Error %s\n", path.c_str(),
             SDL_GetError());
    }

    // Get rid of old loaded surface;
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
}

void _testDrawing(SDL *s) {
  // Clear SDL_CreateRenderer
  SDL_SetRenderDrawColor(s->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(s->gRenderer);

  // Render filled quad.
  SDL_Rect fillRect = {s->SCREEN_WIDHT / 4, s->SCREEN_HEIGHT / 4,
                       s->SCREEN_WIDHT / 2, s->SCREEN_HEIGHT / 2};
  SDL_SetRenderDrawColor(s->gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(s->gRenderer, &fillRect);

  // Render green outline quad
  SDL_Rect outlineRect = {s->SCREEN_WIDHT / 4, s->SCREEN_HEIGHT / 6,
                          s->SCREEN_WIDHT * 2 / 3, s->SCREEN_HEIGHT * 2 / 3};
  SDL_SetRenderDrawColor(s->gRenderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawRect(s->gRenderer, &outlineRect);

  // Draw blue horizontal linear
  SDL_SetRenderDrawColor(s->gRenderer, 0x00, 0x00, 0xFF, 0xFF);
  SDL_RenderDrawLine(s->gRenderer, 0, s->SCREEN_HEIGHT / 2, s->SCREEN_WIDHT,
                     s->SCREEN_HEIGHT / 2);

  // Draw vertical line of yellow dots.
  SDL_SetRenderDrawColor(s->gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
  for (int i = 0; i < s->SCREEN_HEIGHT; i += 4)
    SDL_RenderDrawPoint(s->gRenderer, s->SCREEN_WIDHT / 2, i);
}

void sSDL_init_struct(SDL *s) {
  s->init = _init;
  s->close = _close;
  s->loadMedia = _loadMedia;
  s->loadTexture = _loadTexture;
  s->gWindow = NULL;
  s->gRenderer = NULL;
  s->testDrawing = _testDrawing;
}
