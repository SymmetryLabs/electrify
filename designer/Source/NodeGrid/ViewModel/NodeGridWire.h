#pragma once

#include "BlueprintUiGlobals.h"

#include <node_wire.h>

#include "BlueprintUiObject.h"
#include "NodeGridItem.h"

class NodeGrid;

class NodeGridWire : public BlueprintUiObject {

public:
    NodeGridWire(NodeWire* nodeWire, NodeGrid& nodeGrid,
                 NodeGridItem* emittingGridItem, NodeGridItem* receivingGridItem);
    NodeGridWire(NodeGrid& nodeGrid,
                 NodeGridItem* emittingGridItem, string emittingOutputName,
                 NodeGridItem* receivingGridItem, string receivingInputName);

    NodeWire* nodeWire;

    NodeGridItem* emittingGridItem;
    NodeGridItem* receivingGridItem;
    
    string emittingOutputName;
    string receivingInputName;
    
    VarSignalT<Point<int>> emittingPos;
    VarSignalT<Point<int>> receivingPos;
    
    void setOtherPosition(Point<int> pos);

private:

    NodeGrid& nodeGrid;

};
