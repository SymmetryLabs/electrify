#include "constant_color_node.h"

Color ConstantColorNode::calculate(const FrameContext&) const
{
  return color;
}
