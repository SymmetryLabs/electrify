#pragma once
#include "globals.h"

class Model;
class FrameContext;
class Color;

class Renderable {

public:
    virtual ~Renderable() = default;

    virtual void initRenderable(const Model&) {}
    virtual void deinitRenderable() {}

    virtual void updateRenderable(const FrameContext&) {}
    virtual void renderRenderable(const FrameContext&, vector<Color>&) {}

};
