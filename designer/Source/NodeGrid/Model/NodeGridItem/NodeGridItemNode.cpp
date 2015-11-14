/*
  ==============================================================================

    NodeGridItemNode.cpp
    Created: 1 Sep 2015 4:42:16pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemNode.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>


#include "NodeGrid.h"
#include "NodeGridSocket.h"

NodeGridItemNode::NodeGridItemNode(NodeHandle& node, NodeGrid& nodeGrid)
: NodeGridItem(node, nodeGrid)
, node(node)
{
    node.getInputs().makeSlave(inputs, nodeGrid, NodeGridSocketDirection::INPUT);
    node.getOutputs().makeSlave(outputs, nodeGrid, NodeGridSocketDirection::OUTPUT);
    
    init();
}

string NodeGridItemNode::getName() const
{
    return node.getName();
}

string NodeGridItemNode::getId() const
{
    return boost::lexical_cast<std::string>(node.uuid);
}

void NodeGridItemNode::deleteSelectable()
{
    nodeGrid.removeNode(*this);
}
