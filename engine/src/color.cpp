#include "color.h"

#include <hsv2rgb.h>

void Color::fromHSV(double h, double s, double v)
{
  CHSV hsv {static_cast<uint8_t>(255 * h), static_cast<uint8_t>(255 * s), static_cast<uint8_t>(255 * v)};
  CRGB rgb;
  hsv2rgb_rainbow(hsv, rgb);
  _rgba = (rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8);
}
