#include "../include/dept_hist.h"
#include <algorithm>
#include <vector>

DepthHist::DepthHist(uint32_t min, uint32_t max, uint32_t bins, uint32_t height,
                     uint32_t width) {
  sSDL_init_struct(&s);
  s.init(&s);
  ft.init("/usr/share/fonts/truetype/hack/Hack-Regular.ttf", &s);
  dl.init(&s);

  this->max = max;
  this->min = min;
  this->height = height;
  this->width = width;
  this->bins = bins;
}
DepthHist::~DepthHist() { s.close(&s); }
void DepthHist::step() {
  SDL_RenderPresent(s.gRenderer);
}
void DepthHist::display(const short *data) {
  std::vector<uint32_t> hist(bins, 0);
  uint16_t hist_max = data[0];
  uint32_t dh = static_cast<uint32_t>(floor(((max - min) * 1.0f) / bins));
  for (uint32_t i = 0; i < width * height; ++i) {
    uint32_t idx = static_cast<uint32_t>(floor((data[i] * 1.0f) / bins));
    hist_max = (data[i] > hist_max) ? data[i] : hist_max;
    hist[idx]++;
  }

  uint16_t screen_width = s.SCREEN_WIDHT - 20;
  uint16_t screen_height = s.SCREEN_HEIGHT - 20;
  uint16_t dw = static_cast<uint16_t>(float((screen_width * 1.0f) / bins));
  uint16_t x = 20;
  uint16_t y = s.SCREEN_HEIGHT - 20;
  std::vector<uint32_t>::iterator max_it =
      std::max_element(hist.begin(), hist.end());
  uint32_t max_el = *max_it;
  double screne_height_ratio = (screen_height * 1.0f) / max_el;

  uint32_t old_color = dl.getColor();
  dl.setColor(RGB(51,0,25));

  for (uint32_t i = 0; i < bins; ++i) {
    double dh = hist[i] * screne_height_ratio;
    dl.FillRect(Point{x, y},
                dw, (uint16_t)(floor(dh)));
    x+=dw;
  }
  char str[128];
  sprintf(str, "%d", hist_max);
  ft.renderText(Point{300, 40}, str );
  dl.setColor(old_color);
}

void DepthHist::handle_keys(SDL_Event const &e) {
  auto code = e.key.keysym.scancode;
  switch (e.type) {
  case SDL_KEYDOWN:
    if (code == 0x29 || code == 0x28 || code == 0x14)
      quit = true;
    if (code == 0x06) {
      SDL_SetRenderDrawColor(s.gRenderer, 0x00, 0x00, 0xFF, 0xFF);
      uint8_t r = 0, g = 0, b = 0, a = 0;
      SDL_GetRenderDrawColor(s.gRenderer, &r, &g, &b, &a);
      printf("The currently used color is #%02X%02X%02X%02X\n", r, g, b, a);
    }
    break;
  case SDL_QUIT:
    quit = true;
    break;
  default:
    break;
  }
}
void DepthHist::draw_coordinates() {
  dl.ClrScr();
  dl.setColor(RGB(0, 0, 0));
  dl.Line(
      Point{10, (uint16_t)(s.SCREEN_HEIGHT - 20)},
      Point{(uint16_t)(s.SCREEN_WIDHT - 10), (uint16_t)(s.SCREEN_HEIGHT - 20)});
  dl.Line(Point{20, 20}, Point{20, (uint16_t)(s.SCREEN_HEIGHT - 10)});

  double df = (s.SCREEN_WIDHT - 20) / 256.0f;
  for (uint16_t i = 0; i < 256; ++i) {
    if (i % 8 == 0)
      dl.Line(
          Point{(uint16_t)(20 + (i * df)), (uint16_t)(s.SCREEN_HEIGHT - 10)},
          Point{(uint16_t)(20 + (i * df)), (uint16_t)(s.SCREEN_HEIGHT - 30)});
  }
}
