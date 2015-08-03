#include "node_grid_item.h"

NodeGridItem::NodeGridItem(NodeProxy<EngineUiDomain>* node_)
  : node(node_)
{
  // TODO: load persisted x,y for node
}

void NodeGridItem::setPos(float x_, float y_)
{
  x <<= x_;
  y <<= y_;
}
