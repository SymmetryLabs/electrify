#pragma once
#include "constants.h"

class Color
{
  private:
    unsigned int _rgba =0;
  public:
  	explicit Color(unsigned int color) {_rgba = color;};
  	Color() {Color(0);};
    void* asHSB(); //TODO pick a data format
    void* asHSL(); //TODO pick a data format
    void* asRGB(); //TODO pick a data format
    unsigned int asRGBA() {return _rgba;};
    void fromHSB(double h, double s, double b);
    void fromHSL(double h, double s, double l);
    void fromRGB(double r, double g, double b);
    void fromRGBA(unsigned int rgba) {_rgba=rgba;};

};
