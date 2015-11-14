/*
  ==============================================================================

    NodeGridItemSocket.cpp
    Created: 1 Sep 2015 4:42:25pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemSocket.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <node_socket.h>

#include "NodeGrid.h"
#include "NodeGridSocket.h"

NodeGridItemSocket::NodeGridItemSocket(NodeSocket& nodeSocket, NodeGrid& nodeGrid)
: NodeGridItem(nodeSocket, nodeGrid)
, nodeSocket(nodeSocket)
{
    inputs.push_back(make_shared<NodeGridSocket>(nodeSocket, nodeGrid, NodeGridSocketDirection::INPUT));
    
    init();
}

string NodeGridItemSocket::getName() const
{
    return nodeSocket.getName();
}

string NodeGridItemSocket::getId() const
{
    return boost::lexical_cast<std::string>(nodeSocket.getNodeHandle().uuid) + "_" + nodeSocket.getName();
}

void NodeGridItemSocket::deleteSelectable()
{
}
