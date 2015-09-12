#include "renderer.h"

#include "double_buffer.h"
#include "color.h"

Renderer::Renderer(DoubleBuffer<Color>& doubleBuffer_)
: doubleBuffer(doubleBuffer_)
{
}

void Renderer::copyColorBuffer(vector<Color>& colorBuffer)
{
    doubleBuffer.copyBuffer(colorBuffer);
}
