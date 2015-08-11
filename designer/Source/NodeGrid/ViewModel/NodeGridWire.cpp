#include "NodeGridWire.h"

#include "NodeGrid.h"

NodeGridWire::NodeGridWire(NodeWire& nodeWire, NodeGrid& nodeGrid,
    NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem)
    : nodeWire(nodeWire)
    , emittingGridItem(emittingGridItem)
    , receivingGridItem(receivingGridItem)
    , nodeGrid(nodeGrid)
{
}