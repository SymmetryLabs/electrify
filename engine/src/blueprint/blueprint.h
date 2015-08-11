#pragma once
#include "globals.h"

#include "compound_node.h"
#include "renderable.h"
#include "socket.h"

class Blueprint : public CompoundNode, public Renderable {

public:
    Blueprint();
    virtual ~Blueprint() {}

    static const string nodeName() { return "Blueprint"; }

    virtual void initRenderable(const Model& model_) override;
    virtual void deinitRenderable() override;
    virtual void updateRenderable(const FrameContext& frame) override;
    virtual void renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer) override;

private:
    Socket<Color>* output = nullptr;
    const Model* model = nullptr;

};
