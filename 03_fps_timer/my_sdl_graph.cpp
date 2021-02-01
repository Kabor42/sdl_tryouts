#include "my_sdl_graph.h"

void DrawingLibrary::init(SDL *s) { this->s = s; }
void DrawingLibrary::Line(Point tl, Point br) {
  SDL_RenderDrawLine(s->gRenderer, tl.x, tl.y, br.x, br.y);
}
void DrawingLibrary::Line(Point tl, double angle, uint16_t d) {
  uint8_t dx = static_cast<uint8_t>(tl.x + floor(d * sin(angle)));
  uint8_t dy = static_cast<uint8_t>(tl.y + floor(d * cos(angle)));
  SDL_RenderDrawLine(s->gRenderer, tl.x, tl.y, dx, dy);
}
uint32_t DrawingLibrary::getColor() {
  uint8_t r = 0, g = 0, b = 0, a = 0;
  if (0 == SDL_GetRenderDrawColor(s->gRenderer, &r, &g, &b, &a))
    return RGBA(r, g, b, a);
  return 0;
}
void DrawingLibrary::Rect(Point tl, Point br) {
  SDL_Rect rect = {tl.x, tl.y, br.x - tl.x, br.y - tl.y};
  SDL_RenderDrawRect(s->gRenderer, &rect);
}
void DrawingLibrary::Rect(Point tl, uint16_t width, uint16_t height,
                          double rotation) {
  uint8_t dx = static_cast<uint8_t>(floor(width * sin(rotation)));
  uint8_t dy = static_cast<uint8_t>(floor(height * cos(rotation)));
  SDL_Rect rect = {tl.x, tl.y, dx, dy};
  SDL_RenderDrawRect(s->gRenderer, &rect);
}
void DrawingLibrary::FillRect(Point tl, Point br) {
  SDL_Rect rect = {tl.x, tl.y, br.x - tl.x, br.y - tl.y};
  SDL_RenderFillRect(s->gRenderer, &rect);
}
void DrawingLibrary::FillRect(Point tl, uint16_t width, uint16_t height,
                              double rotation) {
  uint8_t dx = static_cast<uint8_t>(floor(width * sin(rotation)));
  uint8_t dy = static_cast<uint8_t>(floor(height * cos(rotation)));
  SDL_Rect rect = {tl.x, tl.y, dx, dy};
  SDL_RenderFillRect(s->gRenderer, &rect);
}
void DrawingLibrary::setColor(uint32_t color) {
  uint8_t r, g, b, a;
  r = color >> 24;
  g = color >> 16;
  b = color >> 8;
  a = color;
  if (0 != SDL_SetRenderDrawColor(s->gRenderer, r, g, b, a))
    printf("Couldn't set the color!\n SDL_Error: %s\n", SDL_GetError());
}
void DrawingLibrary::ClrScr() {
  uint32_t current_color = getColor();
  setColor(RGB(255, 255, 255));
  SDL_RenderClear(s->gRenderer);
  setColor(current_color);
}
void DrawingLibrary::test() {
  setColor(RGB(255, 255, 255));
  ClrScr();

  setColor(RGB(0, 0, 255));
  FillRect(
      Point{(uint16_t)(s->SCREEN_WIDHT / 4), (uint16_t)(s->SCREEN_HEIGHT / 4)},
      Point{(uint16_t)(s->SCREEN_WIDHT * 3 / 4),
            (uint16_t)(s->SCREEN_HEIGHT * 3 / 4)});

  setColor(RGB(0, 125, 125));
  Rect(Point{(uint16_t)(s->SCREEN_WIDHT / 6), (uint16_t)(s->SCREEN_HEIGHT / 6)},
       Point{(uint16_t)(s->SCREEN_WIDHT * 5 / 6),
             (uint16_t)(s->SCREEN_HEIGHT * 5 / 6)});
  setColor(RGB(255, 0, 0));
  Line(Point{0, (uint16_t)(s->SCREEN_HEIGHT / 2)},
       Point{(uint16_t)(s->SCREEN_WIDHT), (uint16_t)(s->SCREEN_HEIGHT / 2)});
}
