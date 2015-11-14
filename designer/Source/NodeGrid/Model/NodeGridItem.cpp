#include "NodeGridItem.h"

#include <compound_node.h>

#include "NodeGrid.h"
#include "NodeGridSocket.h"

NodeGridItem::NodeGridItem(DataTransmitter& gridItemProxy, NodeGrid& nodeGrid)
: Selectable(&nodeGrid)
, gridItemProxy(gridItemProxy)
, nodeGrid(nodeGrid)
{
}

void NodeGridItem::init()
{
    x = nodeGrid.compoundNode.getValue<float>("item_" + getId() + "_x");
    x.observe([this] (float x) {
        this->nodeGrid.compoundNode.setValue("item_" + getId() + "_x", x);
    });
    y = nodeGrid.compoundNode.getValue<float>("item_" + getId() + "_y");
    y.observe([this] (float y) {
        this->nodeGrid.compoundNode.setValue("item_" + getId() + "_y", y);
    });
}

bool NodeGridItem::containsNodeGridSocket(const NodeGridSocket& nodeGridSocket) const
{
    for (const auto& input : inputs) {
        if (input.get() == &nodeGridSocket) {
            return true;
        }
    }
    for (const auto& output : outputs) {
        if (output.get() == &nodeGridSocket) {
            return true;
        }
    }
    return false;
}

NodeGridSocket* NodeGridItem::gridSocketForNodeSignal(const NodeSignal& nodeSignal) const
{
    for (const auto& input : inputs) {
        if (&input->nodeSignal == &nodeSignal) {
            return input.get();
        }
    }
    for (const auto& output : outputs) {
        if (&output->nodeSignal == &nodeSignal) {
            return output.get();
        }
    }
    return nullptr;
}

void NodeGridItem::setPos(float x_, float y_)
{
    x = x_;
    y = y_;
}
