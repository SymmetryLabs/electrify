#pragma once
#include "constants.h"

#include "value.h"

class Color : public Value {

public:
  explicit Color(unsigned long int color) {_rgba = color;};
  Color() {}

  unsigned int asRGBA() const {return _rgba;};
  void fromHSV(double h, double s, double v);
  void fromRGBA(unsigned long int rgba) {_rgba = rgba;};

private:
  unsigned long int _rgba =0;

};

static inline ostream& operator<<(ostream& os, const Color& color)
{
    os << hex << color.asRGBA();
    return os;
}
