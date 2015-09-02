/*
  ==============================================================================

    NodeGridItemSocket.cpp
    Created: 1 Sep 2015 4:42:25pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemSocket.h"

#include "NodeGrid.h"

NodeGridItemSocket::NodeGridItemSocket(NodeSocketProxy& nodeSocket, NodeGrid& nodeGrid)
: NodeGridItem(nodeGrid)
, nodeSocket(nodeSocket)
{
    inputs.push_back(make_shared<NodeGridSocket>(nodeSocket, nodeGrid, NodeGridSocketDirection::INPUT));
}

string NodeGridItemSocket::getName() const
{
    return nodeSocket.name.getValue();
}

void NodeGridItemSocket::deleteSelectable()
{
}
