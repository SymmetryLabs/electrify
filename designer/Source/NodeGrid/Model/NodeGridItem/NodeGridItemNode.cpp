/*
  ==============================================================================

    NodeGridItemNode.cpp
    Created: 1 Sep 2015 4:42:16pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemNode.h"

#include "NodeGrid.h"

NodeGridItemNode::NodeGridItemNode(NodeProxy& node, NodeGrid& nodeGrid)
: NodeGridItem(nodeGrid)
, node(node)
{
    node.inputs.makeSlave(inputs, nodeGrid, NodeGridSocketDirection::INPUT);
    node.outputs.makeSlave(outputs, nodeGrid, NodeGridSocketDirection::OUTPUT);
}

string NodeGridItemNode::getName() const
{
    return node.name.getValue();
}

void NodeGridItemNode::deleteSelectable()
{
    nodeGrid.removeNode(*this);
}
