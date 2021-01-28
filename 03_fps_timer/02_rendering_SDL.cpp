#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "my_sdl_graph.h"
#include "my_sdl_helper.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>

/* Print modifier info */
void PrintModifiers(uint16_t mod) {
  printf("Modifers: ");

  /* If there are none then say so and return */
  if (mod == KMOD_NONE) {
    printf("None\n");
    return;
  }

  /* Check for the presence of each SDLMod value */
  /* This looks messy, but there really isn't    */
  /* a clearer way.                              */
  if (mod & KMOD_NUM)
    printf("NUMLOCK ");
  if (mod & KMOD_CAPS)
    printf("CAPSLOCK ");
  if (mod & KMOD_LCTRL)
    printf("LCTRL ");
  if (mod & KMOD_RCTRL)
    printf("RCTRL ");
  if (mod & KMOD_RSHIFT)
    printf("RSHIFT ");
  if (mod & KMOD_LSHIFT)
    printf("LSHIFT ");
  if (mod & KMOD_RALT)
    printf("RALT ");
  if (mod & KMOD_LALT)
    printf("LALT ");
  if (mod & KMOD_CTRL)
    printf("CTRL ");
  if (mod & KMOD_SHIFT)
    printf("SHIFT ");
  if (mod & KMOD_ALT)
    printf("ALT ");
  printf("\n");
}

int main(int argc, char *argv[]) {
  SDL s;
  sSDL_init_struct(&s);

  DrawingLibrary dl(&s);

  auto fpsDelay = std::chrono::milliseconds(33);
  auto t1 = std::chrono::high_resolution_clock::now();

  s.timer.start();

  if (!s.init(&s)) {
    printf("Failed to initialize!\n");
  } else {
    if (!s.loadMedia(&s)) {
      printf("Failed to load media!\n");
    } else {
      // Main loop
      bool quit = false;

      SDL_Event e;

      while (!quit) {
        t1 = std::chrono::high_resolution_clock::now();
        // Handle events
        while (SDL_PollEvent(&e) != 0)
          switch (e.type) {
          case SDL_KEYDOWN:
            // printf("Scancode: 0x%02X", e.key.keysym.scancode);
            // printf(", Name: %s", SDL_GetKeyName( e.key.keysym.sym));
            // printf("\n");
            // PrintModifiers(e.key.keysym.mod);
            if (e.key.keysym.scancode == 0x29 ||
                e.key.keysym.scancode == 0x28 || e.key.keysym.scancode == 0x14)
              quit = true;
            if (e.key.keysym.scancode == 0x06) {
              SDL_SetRenderDrawColor(s.gRenderer, 0x00, 0x00, 0xFF, 0xFF);
              uint8_t r = 0, g = 0, b = 0, a = 0;
              SDL_GetRenderDrawColor(s.gRenderer, &r, &g, &b, &a);
              printf("The currently used color is #%02X%02X%02X%02X\n", r, g, b,
                     a);
            }
            break;
          case SDL_QUIT:
            quit = true;
            break;
          default:
            break;
          }

        // s.testDrawing(&s);
        dl.test();

        dl.setColor(RGB(0, 0, 0));
        dl.Line(Point{10, (uint16_t)(s.SCREEN_HEIGHT - 20)},
                Point{(uint16_t)(s.SCREEN_WIDHT - 10),
                      (uint16_t)(s.SCREEN_HEIGHT - 20)});
        dl.Line(Point{20, 20}, Point{20, (uint16_t)(s.SCREEN_HEIGHT - 10)});

        double df = (s.SCREEN_WIDHT - 20) / 256.0f;
        for (uint16_t i = 0; i < 256; ++i) {
          if (i % 8 == 0)
            dl.Line(Point{(uint16_t)(20 + (i * df)),
                          (uint16_t)(s.SCREEN_HEIGHT - 10)},
                    Point{(uint16_t)(20 + (i * df)),
                          (uint16_t)(s.SCREEN_HEIGHT - 30)});
        }

        // Update screen
        SDL_RenderPresent(s.gRenderer);

        auto t2 = std::chrono::high_resolution_clock::now();
        auto diff = t2 - t1;
        if (diff < fpsDelay)
          std::this_thread::sleep_until(t1 + fpsDelay);
        /*
        printf("              \r");
        printf("%ld/%ldms",
            std::chrono::duration_cast<std::chrono::milliseconds>(diff).count(),
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()
        - t1).count()); fflush(stdout);
        */
      }
    }
  }

  s.timer.stop();
  s.close(&s);

  return 0;
}
