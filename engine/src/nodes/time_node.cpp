#include "time_node.h"

float TimeNode::calculate(const FrameContext& frame) const
{
    return frame.timeSeconds();
}
