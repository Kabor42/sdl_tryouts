#include "my_sdl_ttf.h"

Font::Font(std::string path, SDL *s) {
  font = TTF_OpenFont(path.c_str(), 24);
  if (NULL == font)
    printf("Couldn't open font!\nTFF_Error: %s\n", TTF_GetError());

  this->s = s;
  color = {0, 0, 0, 0};
}

void Font::init() {
  for (uint8_t i = 0; i < 10; ++i) {
    char digit = '0' + i;
    SDL_Surface *surface = TTF_RenderText_Solid(font, &digit, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(s->gRenderer, surface);
    digits.push_back(Text{texture, (uint8_t)surface->w, (uint8_t)surface->h});
    SDL_FreeSurface(surface);
  }
}

void Font::renderInteger(Point tl,int d) {
    char number[256];
    sprintf(number, "%d", d);
    int prevx = tl.x;
    for(uint32_t i=0; i < strlen(number); ++i) {
        int idx = number[i] - '0';
        SDL_Rect rect = {prevx, tl.y, digits[idx].width, digits[idx].height};
        prevx += digits[idx].width;
        SDL_RenderCopy(s->gRenderer, digits[idx].texture, NULL, &rect);
    }
}

void Font::renderFloat(Point tl, double d) {
  char number[256];
  sprintf( number, "%lf", d);
  int prevx = tl.x;
  for(uint32_t i=0; i < strlen(number); ++i ) {
    int idx = number[i] - '0';
    SDL_Rect rect = {prevx, tl.y, digits[idx].width, digits[idx].height};
    prevx += digits[idx].width;
    SDL_RenderCopy(s->gRenderer, digits[idx].texture, NULL, &rect);
  }
}

void Font::renderText(Point tl, std::string str) {
  SDL_Surface *surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(s->gRenderer, surface);
  SDL_Rect rect = { tl.x, tl.y, surface->w, surface->h};
  SDL_RenderCopy(s->gRenderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
}
