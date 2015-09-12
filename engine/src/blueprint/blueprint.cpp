#include "blueprint.h"

#include "color.h"
#include "model.h"

unique_ptr<Renderable> Blueprint::releaseRenderable(DataBridge& dataBridge)
{
    auto node = releaseNode(dataBridge);
    auto blueprintNode = dynamic_pointer_cast<BlueprintNode>(node);
    auto renderable = make_unique<BlueprintRenderable>(blueprintNode);
    return move(renderable);
}

shared_ptr<Blueprint> makeBlueprint()
{
    return makeNodeHandle<BlueprintNode>();
}

BlueprintNode::BlueprintNode(Blueprint& nodeHandle)
: CompoundNode(nodeHandle)
{
    nodeHandle.setName("Blueprint");
    nodeHandle.registerWirableOutput("color", &output);
}

BlueprintRenderable::BlueprintRenderable(const shared_ptr<BlueprintNode>& blueprintNode_)
: blueprintNode(blueprintNode_)
{
}

void BlueprintRenderable::initRenderable(const Model& model_)
{
    blueprintNode->init();
    model = &model_;
}

void BlueprintRenderable::deinitRenderable()
{
    blueprintNode->deinit();
    model = nullptr;
}

void BlueprintRenderable::updateRenderable(const FrameContext& frame)
{
    blueprintNode->update(frame);
}

void BlueprintRenderable::renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer)
{
    // rasterize to color buffer
    int i = 0;
    for (const auto& pixel : model->pixels) {
        FragmentContext frag(*pixel);
        FrameContext childFrame(frame, &frag);
        colorBuffer[i++] = blueprintNode->output(childFrame);
    }
}
