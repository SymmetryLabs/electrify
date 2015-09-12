#include "NodeGrid.h"

#include <compound_node.h>

#include "NodeGridWire.h"
#include "NodeGridSocket.h"
#include "NodeGridItemNode.h"
#include "NodeGridItemSocket.h"

NodeGrid::NodeGrid(CompoundNodeHandle& compoundNode_)
: compoundNode(compoundNode_)
{
    compoundNode.subnodes.makeSlave(gridItems, *this);
    compoundNode.getWirableOutputs().makeSlave(gridOutputs, *this);
    compoundNode.nodeWires.makeSlave(gridWires, [this] (const shared_ptr<NodeWire>& nodeWire) {
        return make_shared<NodeGridWire>(*nodeWire.get(), *this, gridSocketForNodeSignal(nodeWire->source), gridSocketForNodeSignal(nodeWire->destination));
    });
}

void NodeGrid::addNode(string name, float x, float y)
{
    auto pos = compoundNode.createSubnode(name);
    gridItems[pos]->setPos(x, y);
}

void NodeGrid::removeNode(NodeGridItemNode& gridItem)
{
    compoundNode.removeSubnode(gridItem.node);
}

void NodeGrid::removeWire(NodeGridWire& gridWire)
{
    compoundNode.removeWire(*gridWire.nodeWire);
}

NodeGridSocket* NodeGrid::gridSocketForNodeSignal(NodeSignal& nodeSignal)
{
    for (auto& gridItem : gridItems) {
        auto socket = gridItem->gridSocketForNodeSignal(nodeSignal);
        if (socket) {
            return socket;
        }
    }
    for (auto& gridItem : gridOutputs) {
        auto socket = gridItem->gridSocketForNodeSignal(nodeSignal);
        if (socket) {
            return socket;
        }
    }
    return nullptr;
}

void NodeGrid::draggingWireStarted(NodeGridSocket& socket)
{
    shared_ptr<NodeGridWire> wire;
    switch (socket.direction) {
        case NodeGridSocketDirection::INPUT:
            wire = make_shared<NodeGridWire>(*this, nullptr, &socket);
            break;
        case NodeGridSocketDirection::OUTPUT:
            wire = make_shared<NodeGridWire>(*this, &socket, nullptr);
            break;
    }
    draggingWire << wire;
}

void NodeGrid::draggingWireMoved(Point<int> p)
{
    if (draggingWire.getValue()) {
        draggingWire.getValue()->setOtherPosition(p);
    }
}

void NodeGrid::draggingWireEnded(NodeGridSocket* socket)
{
    if (draggingWire.getValue()) {
        if (socket) {
            switch (socket->direction) {
                case NodeGridSocketDirection::INPUT:
                    compoundNode.wireSubnodes(draggingWire.getValue()->emittingGridSocket->nodeSignal, dynamic_cast<NodeSocket&>(socket->nodeSignal));
                    break;
                case NodeGridSocketDirection::OUTPUT:
                    compoundNode.wireSubnodes(socket->nodeSignal, dynamic_cast<NodeSocket&>(draggingWire.getValue()->receivingGridSocket->nodeSignal));
                    break;
            }
        }
        draggingWire << nullptr;
    }
}
