#include "NodeGridItem.h"

#include "NodeGrid.h"

NodeGridItem::NodeGridItem(NodeProxy& node, NodeGrid& nodeGrid)
: Selectable(&nodeGrid)
, node(node)
, nodeGrid(nodeGrid)
{
    node.inputs.makeSlave(inputs, nodeGrid, this);
    node.outputs.makeSlave(outputs, nodeGrid, this);
}

NodeGridSocket* NodeGridItem::gridSocketForNodeSignal(NodeSignalProxy& nodeSignal)
{
    for (auto& input : inputs) {
        if (&input->nodeSignal == &nodeSignal) {
            return input.get();
        }
    }
    for (auto& output : outputs) {
        if (&output->nodeSignal == &nodeSignal) {
            return output.get();
        }
    }
    return nullptr;
}

void NodeGridItem::setPos(float x_, float y_)
{
    x << x_;
    y << y_;
}

void NodeGridItem::deleteSelectable()
{
    nodeGrid.removeNode(*this);
}
