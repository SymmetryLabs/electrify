/*
  ==============================================================================

    NodeGridSocket.cpp
    Created: 24 Aug 2015 6:57:27pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridSocket.h"

NodeGridSocket::NodeGridSocket(NodeSignalProxy& nodeSignal, NodeGrid& nodeGrid, NodeGridItem* gridItem)
: nodeSignal(nodeSignal)
, nodeGrid(nodeGrid)
, gridItem(gridItem)
{
}