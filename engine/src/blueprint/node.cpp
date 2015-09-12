#include "node.h"

Node::Node(NodeHandle& nodeHandle)
: DataTransmitter(nodeHandle.shared_from_this())
{
}
