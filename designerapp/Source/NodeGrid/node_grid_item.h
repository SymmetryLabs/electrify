#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "node.h"
#include "grid_item_coordinator.h"

class NodeGridItem : public BlueprintUiObject {

public:
    NodeGridItem(NodeProxy<EngineUiDomain>* node, GridItemCoordinator& gridItemCoordinator);

    NodeProxy<EngineUiDomain>* node;

    VarSignalT<float> x;
    VarSignalT<float> y;
    void setPos(float x, float y);

    VarSignalT<bool> selected;
    void setSelected(bool selected);

private:
    GridItemCoordinator& gridItemCoordinator;

    friend class GridItemCoordinator;

};
