#include "node_grid_wire.h"

NodeGridWire::NodeGridWire(NodeWire& nodeWire, GridItemCoordinator& gridItemCoordinator,
  NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem)
  : nodeWire(nodeWire)
  , emittingGridItem(emittingGridItem)
  , receivingGridItem(receivingGridItem)
  , gridItemCoordinator(gridItemCoordinator)
{
}