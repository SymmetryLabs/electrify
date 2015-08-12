#include "NodeGridWire.h"

#include "NodeGrid.h"

NodeGridWire::NodeGridWire(NodeWire* nodeWire, NodeGrid& nodeGrid,
    NodeGridItem* emittingGridItem, NodeGridItem* receivingGridItem)
    : nodeWire(nodeWire)
    , emittingGridItem(emittingGridItem)
    , receivingGridItem(receivingGridItem)
    , emittingOutputName(nodeWire->emittingOutputName)
    , receivingInputName(nodeWire->receivingInputName)
    , emittingPos(MakeVar<EngineUiDomain>(Point<int>()))
    , receivingPos(MakeVar<EngineUiDomain>(Point<int>()))
    , nodeGrid(nodeGrid)
{
}

NodeGridWire::NodeGridWire(NodeGrid& nodeGrid,
                           NodeGridItem* emittingGridItem, string emittingOutputName,
                           NodeGridItem* receivingGridItem, string receivingInputName)
: nodeWire(nullptr)
, emittingGridItem(emittingGridItem)
, receivingGridItem(receivingGridItem)
, emittingOutputName(emittingOutputName)
, receivingInputName(receivingInputName)
, emittingPos(MakeVar<EngineUiDomain>(Point<int>()))
, receivingPos(MakeVar<EngineUiDomain>(Point<int>()))
, nodeGrid(nodeGrid)
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
