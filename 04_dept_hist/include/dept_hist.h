#ifndef __DOMI_MY_SDL_DEPTH_HIST_H__
#define __DOMI_MY_SDL_DEPTH_HIST_H__

#include "my_sdl_helper.h"
#include "my_sdl_graph.h"
#include "my_sdl_ttf.h"
#include <cstdint>

class DepthHist {
  public:
    DepthHist(uint32_t min, uint32_t max, uint32_t bins, uint32_t height,
              uint32_t width);
    ~DepthHist();
    void display(const short *);
    bool quit;
    void handle_keys(SDL_Event const &);
    void draw_coordinates();
    void step();
  private:
    SDL s;
    Font ft;
    DrawingLibrary dl;
    uint32_t min, max;
    uint32_t height, width;
    uint32_t bins;
};

#endif // __DOMI_MY_SDL_DEPTH_HIST_H__
