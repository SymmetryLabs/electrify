#include "NodeGridWire.h"

NodeGridWire::NodeGridWire(NodeWire& nodeWire, GridItemCoordinator& gridItemCoordinator,
    NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem)
    : nodeWire(nodeWire)
    , emittingGridItem(emittingGridItem)
    , receivingGridItem(receivingGridItem)
    , gridItemCoordinator(gridItemCoordinator)
{
}