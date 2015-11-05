#include "renderer.h"

#include "double_buffer.h"
#include "color.h"

Renderer::Renderer(DoubleBuffer<Color>& doubleBuffer_)
: doubleBuffer(doubleBuffer_)
{
}

unsigned int Renderer::copyColorBuffer(unsigned int id, vector<Color>& colorBuffer) const
{
    return doubleBuffer.copyBuffer(id, colorBuffer);
}
