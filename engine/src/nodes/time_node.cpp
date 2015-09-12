#include "time_node.h"

TimeNode::TimeNode(NodeHandle& nodeHandle)
: BasicNode<float>(nodeHandle)
{
    nodeHandle.setName("Time");
}

float TimeNode::calculate(const FrameContext& frame) const
{
    return frame.timeSeconds();
}
