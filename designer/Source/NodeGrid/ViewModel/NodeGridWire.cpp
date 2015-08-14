#include "NodeGridWire.h"

#include "NodeGrid.h"

NodeGridWire::NodeGridWire(NodeWire* nodeWire, NodeGrid& nodeGrid,
    NodeGridItem* emittingGridItem, NodeGridItem* receivingGridItem)
    : nodeWire(nodeWire)
    , emittingGridItem(emittingGridItem)
    , receivingGridItem(receivingGridItem)
    , emittingSocket(nodeWire->emittingSocket)
    , receivingSocket(nodeWire->receivingSocket)
    , emittingPos(MakeVar<EngineUiDomain>(Point<int>()))
    , receivingPos(MakeVar<EngineUiDomain>(Point<int>()))
{
}

NodeGridWire::NodeGridWire(NodeGridItem* emittingGridItem, NodeSocket emittingSocket,
                           NodeGridItem* receivingGridItem, NodeSocket receivingSocket)
: nodeWire(nullptr)
, emittingGridItem(emittingGridItem)
, receivingGridItem(receivingGridItem)
, emittingSocket(emittingSocket)
, receivingSocket(receivingSocket)
, emittingPos(MakeVar<EngineUiDomain>(Point<int>()))
, receivingPos(MakeVar<EngineUiDomain>(Point<int>()))
{
}

void NodeGridWire::setOtherPosition(Point<int> pos)
{
    if (!emittingGridItem) {
        emittingPos <<= pos;
    } else if (!receivingGridItem) {
        receivingPos <<= pos;
    }
}
