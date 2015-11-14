#include "blueprint.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include "color.h"
#include "model.h"
#include "blueprint_serializer.h"

CEREAL_REGISTER_TYPE(Blueprint);

unique_ptr<Renderable> Blueprint::releaseRenderable(DataBridge& dataBridge)
{
    setBridge(dataBridge);
    auto blueprintNode = dynamic_pointer_cast<BlueprintNode<FunctionContainer>>(node);
    return make_unique<BlueprintRenderable>(blueprintNode);
}

void Blueprint::generateNode()
{
    generateNodeForHandle<BlueprintNode>(*this);
}

shared_ptr<Blueprint> makeBlueprint()
{
    return makeNodeHandle<BlueprintNode>("BlueprintNode");
}

BlueprintRenderable::BlueprintRenderable(const shared_ptr<BlueprintNode<FunctionContainer>>& blueprintNode_)
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
    assert(model);
    blueprintNode->update(frame);
}

void BlueprintRenderable::renderRenderable(const FrameContext& frame, vector<Color>& colorBuffer)
{
    assert(model);
    // rasterize to color buffer
    int i = 0;
    for (const auto& pixel : model->pixels) {
        assert(pixel);
        FragmentContext frag(*pixel);
        FrameContext childFrame(frame, &frag);
        colorBuffer[i++] = blueprintNode->output(childFrame);
    }
}

BlueprintNode<FunctionContainer>& BlueprintRenderable::getBlueprintNode() const
{
    return *blueprintNode;
}
