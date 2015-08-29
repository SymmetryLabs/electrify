#include "time_node.h"

TimeNode::TimeNode()
: BasicNode<float>("Time")
{
}

float TimeNode::calculate(const FrameContext& frame) const
{
    return frame.timeSeconds();
}
