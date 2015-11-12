#pragma once
#include "globals.h"

template<typename>
class DoubleBuffer;
class Color;

class Renderer {

public:
    explicit Renderer(DoubleBuffer<Color>& doubleBuffer);

    unsigned int copyColorBuffer(unsigned int id, vector<Color>& colorBuffer) const;

private:
    DoubleBuffer<Color>& doubleBuffer;

};
