#include "node_grid_wire.h"

NodeGridWire::NodeGridWire(NodeWire& nodeWire, GridItemCoordinator& gridItemCoordinator,
  NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem)
  : nodeWire(nodeWire)
  , gridItemCoordinator(gridItemCoordinator)
  , emittingGridItem(emittingGridItem)
  , receivingGridItem(receivingGridItem)
{
}