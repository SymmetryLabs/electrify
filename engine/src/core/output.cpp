#include "output.h"

Output::Output(size_t bufferSize)
{
    for (int i = 0; i < bufferSize; i++) {
        colorBuffer.push_back(Color(0xFFFFFFFF));
    }
}

void Output::setRenderer(Renderer* renderer_)
{
    renderer = renderer_;
}

const vector<Color>& Output::getColorBuffer() const
{
    return colorBuffer;
}

void Output::populateFrame()
{
    if (renderer) {
        renderer->copyColorBuffer(colorBuffer);
    }
}
