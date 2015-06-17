#pragma once
#include "constants.h"

#include "value.h"

class Color : public Value {

private:
  unsigned long int _rgba =0;

public:
  explicit Color(unsigned long int color) {_rgba = color;};
  Color() {Color(0);};

  void* asHSB(); //TODO pick a data format
  void* asHSL(); //TODO pick a data format
  void* asRGB(); //TODO pick a data format
  unsigned int asRGBA() const {return _rgba;};
  void fromHSB(double h, double s, double b);
  void fromHSL(double h, double s, double l);
  void fromRGB(double r, double g, double b);
  void fromRGBA(unsigned long int rgba) {_rgba = rgba;};

};

static inline ostream& operator<<(ostream& os, const Color& color)
{
    os << hex << color.asRGBA();
    return os;
}
