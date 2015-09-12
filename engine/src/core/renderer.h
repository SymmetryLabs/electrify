#pragma once
#include "globals.h"

template<typename>
class DoubleBuffer;
class Color;

class Renderer {

public:
    explicit Renderer(DoubleBuffer<Color>& doubleBuffer);
    
    void copyColorBuffer(vector<Color>& colorBuffer);

private:
    DoubleBuffer<Color>& doubleBuffer;

};
