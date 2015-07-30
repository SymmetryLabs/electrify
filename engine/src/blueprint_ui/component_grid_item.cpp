#include "component_grid_item.h"

ComponentGridItem::ComponentGridItem(ComponentProxy<EngineUiDomain>* component_)
  : component(component_)
{
  // TODO: load persisted x,y for component
}

void ComponentGridItem::setPos(float x_, float y_)
{
  x <<= x_;
  y <<= y_;
}
