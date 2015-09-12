#pragma once
#include "globals.h"

#include "color.h"
#include "renderer.h"

class Output {

public:
    explicit Output(size_t bufferSize);

    void setRenderer(Renderer* renderer);

    const vector<Color>& getColorBuffer() const;

    void populateFrame();

private:
    vector<Color> colorBuffer;

    Renderer* renderer = nullptr;

};
