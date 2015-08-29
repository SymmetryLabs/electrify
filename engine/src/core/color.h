#pragma once
#include "globals.h"

class Color {

public:
    explicit Color(unsigned long int color) {_rgba = color;};
    Color() {}

    unsigned int asRGBA() const {return _rgba;};
    void fromHSV(double h, double s, double v);
    void fromRGBA(unsigned long int rgba) {_rgba = rgba;};

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

private:
    unsigned long int _rgba =0;

};

static inline ostream& operator<<(ostream& os, const Color& color)
{
        os << hex << color.asRGBA();
        return os;
}
