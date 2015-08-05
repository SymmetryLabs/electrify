#include "node_grid_item.h"

NodeGridItem::NodeGridItem(NodeProxy<EngineUiDomain>* node_)
  : node(node_)
  , x(MakeVar<EngineUiDomain, float>(0))
  , y(MakeVar<EngineUiDomain, float>(0))
  , positionChanged(Tokenize(Monitor(x) | Monitor(y)))
{
  // TODO: load persisted x,y for node
}

void NodeGridItem::setPos(float x_, float y_)
{
  x <<= x_;
  y <<= y_;
}
