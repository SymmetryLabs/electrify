/*
  ==============================================================================

    NodeGridSocket.cpp
    Created: 24 Aug 2015 6:57:27pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridSocket.h"

NodeGridSocket::NodeGridSocket(NodeSignal& nodeSignal, NodeGrid& nodeGrid, const NodeGridSocketDirection& direction)
: nodeSignal(nodeSignal)
, nodeGrid(nodeGrid)
, direction(direction)
{
}