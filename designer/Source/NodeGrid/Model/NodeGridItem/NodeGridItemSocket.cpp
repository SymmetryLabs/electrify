/*
  ==============================================================================

    NodeGridItemSocket.cpp
    Created: 1 Sep 2015 4:42:25pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemSocket.h"

#include <node_socket.h>

#include "NodeGrid.h"
#include "NodeGridSocket.h"

NodeGridItemSocket::NodeGridItemSocket(NodeSocket& nodeSocket, NodeGrid& nodeGrid)
: NodeGridItem(nodeSocket, nodeGrid)
, nodeSocket(nodeSocket)
{
    inputs.push_back(make_shared<NodeGridSocket>(nodeSocket, nodeGrid, NodeGridSocketDirection::INPUT));
}

string NodeGridItemSocket::getName() const
{
    return nodeSocket.getName();
}

void NodeGridItemSocket::deleteSelectable()
{
}
