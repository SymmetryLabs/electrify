#pragma once
#include "BlueprintUiGlobals.h"

#include <node_wire.h>

#include "BlueprintUiObject.h"
#include "NodeGridItem.h"

class NodeGrid;

class NodeGridWire : public BlueprintUiObject {

public:
    NodeGridWire(NodeWire& nodeWire, NodeGrid& nodeGrid,
        NodeGridItem& emittingGridItem, NodeGridItem& receivingGridItem);

    NodeWire& nodeWire;

    NodeGridItem& emittingGridItem;
    NodeGridItem& receivingGridItem;

private:

    NodeGrid& nodeGrid;

};
