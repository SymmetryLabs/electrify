#include "component_grid_item.h"

ComponentGridItem::ComponentGridItem(ComponentProxy<EngineUiDomain>* component_)
  : component(component_)
  , x(0)
  , y(0)
{
  // TODO: load persisted x,y for component
}
