/*
  ==============================================================================

    NodeGridItemNode.cpp
    Created: 1 Sep 2015 4:42:16pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemNode.h"

#include "NodeGrid.h"
#include "NodeGridSocket.h"

NodeGridItemNode::NodeGridItemNode(NodeHandle& node, NodeGrid& nodeGrid)
: NodeGridItem(node, nodeGrid)
, node(node)
{
    node.getInputs().makeSlave(inputs, nodeGrid, NodeGridSocketDirection::INPUT);
    node.getOutputs().makeSlave(outputs, nodeGrid, NodeGridSocketDirection::OUTPUT);
}

string NodeGridItemNode::getName() const
{
    return node.getName();
}

void NodeGridItemNode::deleteSelectable()
{
    nodeGrid.removeNode(*this);
}
