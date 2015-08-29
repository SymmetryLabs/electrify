#include "constant_color_node.h"

ConstantColorNode::ConstantColorNode()
: BasicNode<Color>("Constant color")
{
}

Color ConstantColorNode::calculate(const FrameContext&) const
{
    return color;
}
