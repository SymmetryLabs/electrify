#include "constant_color_node.h"

ConstantColorNode::ConstantColorNode(NodeHandle& nodeHandle)
: BasicNode<Color>(nodeHandle)
{
    nodeHandle.setName("Constant color");
}

Color ConstantColorNode::calculate(const FrameContext&) const
{
    return color;
}
