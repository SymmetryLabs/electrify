#include "NodeGridWire.h"

#include "NodeGrid.h"

NodeGridWire::NodeGridWire(NodeWire& nodeWire, NodeGrid& nodeGrid,
                           NodeGridSocket* emittingGridSocket, NodeGridSocket* receivingGridSocket)
: Selectable(&nodeGrid)
, nodeWire(&nodeWire)
, emittingGridSocket(emittingGridSocket)
, receivingGridSocket(receivingGridSocket)
, nodeGrid(nodeGrid)
{
}

NodeGridWire::NodeGridWire(NodeGrid& nodeGrid, NodeGridSocket* emittingGridSocket,
                           NodeGridSocket* receivingGridSocket)
: Selectable(&nodeGrid)
, nodeWire(nullptr)
, emittingGridSocket(emittingGridSocket)
, receivingGridSocket(receivingGridSocket)
, nodeGrid(nodeGrid)
{
}

void NodeGridWire::setOtherPosition(Point<int> pos)
{
    if (!emittingGridSocket) {
        emittingPos = pos;
    } else if (!receivingGridSocket) {
        receivingPos = pos;
    }
}

void NodeGridWire::deleteSelectable()
{
    nodeGrid.removeWire(*this);
}
