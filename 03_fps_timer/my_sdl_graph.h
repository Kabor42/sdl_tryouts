#ifndef __DOMI_MY_SDL_GRAPH_H__
#define __DOMI_MY_SDL_GRAPH_H__

#include "my_sdl_helper.h"
#include "misc.h"

#define RGB(r, g, b)                                                           \
  ((uint8_t)r << 24 | (uint8_t)g << 16 | (uint8_t)b << 8 | 0xFF)
#define RGBA(r, g, b, a)                                                       \
  ((uint8_t)r << 24 | (uint8_t)g << 16 | (uint8_t)b << 8 | (uint8_t)a)

class DrawingLibrary {
  SDL *s;

public:
  DrawingLibrary(SDL *);
  /** Setting color to the SDL renderer.
   *
   * Use @see RGB or @see RGBA to get an uint32_t to use as color.
   */
  void setColor(uint32_t color);
  /** Gets the currently used color from the renderer. */
  uint32_t getColor();
  /** Draw line between two points
   * @param x starting point x
   * @param y starting point y
   * @param dx end point x
   * @param dy end point y
   */
  void Line(Point tl, Point br);
  /** Draw line with starting point, angle and length.
   *
   * @param x starting point x
   * @param y staarting point y
   * @param angle angle of the line
   * @param d length of the line.
   */
  void Line(Point p, double angle, uint16_t d);
  /** Draw rectangle with 2 points.
   *
   * @param tlx Top Left x point.
   * @param tly Top Left y coordinate.
   * @param brx Bottom Right x coordinate.
   * @param bry Bottom Right y coordinate.
   */
  void Rect(Point tl, Point br);
  /** Draw rectangle from start point with width and length and (rotation)
   *
   * @param x starting point coordinate.
   * @param y starting point coordinate.
   * @param height rectangles height.
   * @param width rectangles width.
   * @param rotation rotation angle (optional).
   */
  void Rect(Point tl, uint16_t width, uint16_t height, double rotation = 0);
  /** Draw a filled rectangle with 2 points.
   *
   * @param tlx Top Left x point.
   * @param tly Top Left y coordinate.
   * @param brx Bottom Right x coordinate.
   * @param bry Bottom Right y coordinate.
   */
  void FillRect(Point tl, Point br);
  /** Draw a filled rectangle from start point with width and length and
   * (rotation)
   *
   * @param x starting point coordinate.
   * @param y starting point coordinate.
   * @param height rectangles height.
   * @param width rectangles width.
   * @param rotation rotation angle (optional).
   */
  void FillRect(Point tl, uint16_t width, uint16_t height, double rotation = 0);
  /** Clear screen */
  void ClrScr();
  void test();
};

#endif