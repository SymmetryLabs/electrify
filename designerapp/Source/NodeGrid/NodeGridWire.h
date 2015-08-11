#pragma once
#include "BlueprintUiGlobals.h"

#include <node_wire.h>

#include "BlueprintUiObject.h"
#include "NodeGridItem.h"
#include "GridItemCoordinator.h"

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
