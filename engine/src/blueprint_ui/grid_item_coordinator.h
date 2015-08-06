#pragma once
#include "blueprint_ui_globals.h"

class NodeGridItem;

class GridItemCoordinator {

public:
  void deselectAll();
  void setSelected(NodeGridItem& gridItem, bool selected);

private:
  VarSignal<EngineUiDomain, NodeGridItem*> selectedGridItem = MakeVar<EngineUiDomain, NodeGridItem*>(nullptr);

};
