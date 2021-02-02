#ifndef __DOMI_MY_SDL_TTF_H__
#define __DOMI_MY_SDL_TTF_H__

#include "my_sdl_helper.h"
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "misc.h"

struct Text {
    SDL_Texture **texture;
    uint8_t width;
    uint8_t height;
};

class Font {
    TTF_Font *font;
    std::vector<Text> digits;
    SDL_Color color;
    SDL *s;
    public:
    void init(std::string path, SDL *s, int size);
    void renderInteger(Point tl,int d);
    void renderFloat(Point tl, double d);
    void renderText(Point tl, std::string str);
    
};

#endif
