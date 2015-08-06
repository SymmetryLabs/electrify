#include "node_grid_item.h"

NodeGridItem::NodeGridItem(NodeProxy<EngineUiDomain>* node, GridItemCoordinator& gridItemCoordinator)
  : node(node)
  , gridItemCoordinator(gridItemCoordinator)
  , x(MakeVar<EngineUiDomain, float>(0))
  , y(MakeVar<EngineUiDomain, float>(0))
  , positionChanged(Tokenize(Monitor(x) | Monitor(y)))
  , selected(MakeVar<EngineUiDomain, bool>(false))
{
  // TODO: load persisted x,y for node
}

void NodeGridItem::setPos(float x_, float y_)
{
  x <<= x_;
  y <<= y_;
}

void NodeGridItem::setSelected(bool selected)
{
  gridItemCoordinator.setSelected(*this, selected);
}
