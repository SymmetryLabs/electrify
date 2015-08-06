#include "grid_item_coordinator.h"

#include "node_grid_item.h"

void GridItemCoordinator::deselectAll()
{
  if (selectedGridItem.Value()) {
    DoTransaction<EngineUiDomain>([this] {
      selectedGridItem.Value()->selected <<= false;
      selectedGridItem <<= nullptr;
    });
  }
}

void GridItemCoordinator::setSelected(NodeGridItem& gridItem, bool selected)
{
  if (selected && (&gridItem != selectedGridItem.Value())) {
    // Select
    DoTransaction<EngineUiDomain>([&, this] {
      if (selectedGridItem.Value()) {
        selectedGridItem.Value()->selected <<= false;
      }
      gridItem.selected <<= true;
      selectedGridItem <<= &gridItem;
    });
  } else if (!selected && (&gridItem == selectedGridItem.Value())) {
    // Unselect
    deselectAll();
  }
}
