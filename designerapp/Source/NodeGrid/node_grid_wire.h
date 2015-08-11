#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "node_wire.h"
#include "node_grid_item.h"
#include "grid_item_coordinator.h"

class NodeGridWire : public BlueprintUiObject {

public:
    NodeGridWire(NodeWire& nodeWire, GridItemCoordinator& gridItemCoordinator,
        NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem);

    NodeWire& nodeWire;

    NodeGridItem& emittingGridItem;
    NodeGridItem& receivingGridItem;

private:

    GridItemCoordinator& gridItemCoordinator;

};
