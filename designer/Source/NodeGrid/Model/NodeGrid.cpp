#include "NodeGrid.h"

NodeGrid::NodeGrid(CompoundNodeProxy* compoundNode_)
: compoundNode(compoundNode_)
{
    compoundNode->subnodes.makeSlave(gridItems, *this);
    compoundNode->nodeWires.makeSlave(gridWires, [this] (const shared_ptr<NodeWireProxy>& nodeWire) {
        return make_shared<NodeGridWire>(*nodeWire.get(), *this, gridSocketForNodeSignal(*nodeWire->source.get()), gridSocketForNodeSignal(*nodeWire->destination.get()));
    });
}

void NodeGrid::addNode(string name, float x, float y)
{
    compoundNode->addSubnode(name, [=] (size_t pos) {
        gridItems[pos]->setPos(x, y);
    });
}

void NodeGrid::removeNode(NodeGridItem& gridItem)
{
    compoundNode->removeSubnode(gridItem.node);
}

NodeGridItem* NodeGrid::nodeWithUuid(boost::uuids::uuid uuid)
{
    for (shared_ptr<NodeGridItem> gridItem : gridItems) {
        if (gridItem->node.uuid == uuid) {
            return gridItem.get();
        }
    }
    return nullptr;
}

void NodeGrid::removeWire(NodeGridWire& gridWire)
{
    compoundNode->removeWire(*gridWire.nodeWire);
}

NodeGridSocket* NodeGrid::gridSocketForNodeSignal(NodeSignalProxy& nodeSignal)
{
    for (auto& gridItem : gridItems) {
        auto socket = gridItem->gridSocketForNodeSignal(nodeSignal);
        if (socket) {
            return socket;
        }
    }
    return nullptr;
}

void NodeGrid::draggingWireStarted(NodeGridItem& nodeGridItem, NodeGridSocket& socket)
{
    draggingWire << make_shared<NodeGridWire>(*this, &socket);
}

void NodeGrid::draggingWireMoved(Point<int> p)
{
    if (draggingWire.getValue()) {
        draggingWire.getValue()->setOtherPosition(p);
    }
}

void NodeGrid::draggingWireEnded(NodeGridItem& gridItemEnd, NodeGridSocket& socket)
{
    if (draggingWire.getValue()) {
        compoundNode->wireSubnodes(draggingWire.getValue()->emittingGridSocket->nodeSignal, dynamic_cast<NodeSocketProxy&>(socket.nodeSignal));
        draggingWire << nullptr;
    }
}
