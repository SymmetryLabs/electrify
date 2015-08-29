#include "hsv_node.h"

HsvNode::HsvNode()
: BasicNode<Color>("HSV")
{
    registerInput("hue", &hue);
    registerInput("saturation", &saturation, 1.0f);
    registerInput("value", &value, 1.0f);
}

Color HsvNode::calculate(const FrameContext& frame) const
{
    Color in;
    in.fromHSV(hue(frame), saturation(frame), value(frame));
    return in;
}
