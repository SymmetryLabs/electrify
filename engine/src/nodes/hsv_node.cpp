#include "hsv_node.h"

HsvNode::HsvNode(NodeHandle& nodeHandle)
: BasicNode<Color>(nodeHandle)
{
    nodeHandle.setName("HSV");
    nodeHandle.registerInput("hue", &hue);
    nodeHandle.registerInput("saturation", &saturation, 1.0f);
    nodeHandle.registerInput("value", &value, 1.0f);
}

Color HsvNode::calculate(const FrameContext& frame) const
{
    Color in;
    in.fromHSV(hue(frame), saturation(frame), value(frame));
    return in;
}
