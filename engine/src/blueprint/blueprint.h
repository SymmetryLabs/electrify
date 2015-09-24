#pragma once
#include "globals.h"

#include "compound_node.h"
#include "renderable.h"
#include "socket.h"

class Blueprint : public CompoundNodeHandle {

public:
    unique_ptr<Renderable> releaseRenderable(DataBridge& dataBridge);

};

shared_ptr<Blueprint> makeBlueprint();

template<typename Input>
class BlueprintNode : public CompoundNode<Input> {

public:
    explicit BlueprintNode(Blueprint& nodeHandle);

    SignalFunction<Color> output;

    typedef Blueprint handle_t;

};

class BlueprintRenderable : public Renderable {

public:
    explicit BlueprintRenderable(const shared_ptr<BlueprintNode<FunctionContainer>>& blueprintNode);

    void initRenderable(const Model& model_) override;
    void deinitRenderable() override;
    void updateRenderable(const FrameContext& frame) override;
    void renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer) override;

private:
    shared_ptr<BlueprintNode<FunctionContainer>> blueprintNode;
    const Model* model = nullptr;

};

#include "blueprint.hpp"
