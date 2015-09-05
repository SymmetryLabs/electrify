#pragma once
#include "globals.h"

#include "compound_node.h"
#include "renderable.h"
#include "socket.h"
#include "proxyable.h"

class Blueprint : public CompoundNode, public Renderable {

public:
    explicit Blueprint(const string& name = "Blueprint");
    virtual ~Blueprint() = default;

    virtual void initRenderable(const Model& model_) override;
    virtual void deinitRenderable() override;
    virtual void updateRenderable(const FrameContext& frame) override;
    virtual void renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer) override;

private:
    SignalFunction<Color> output;
    const Model* model = nullptr;

};
