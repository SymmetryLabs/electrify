#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

class NodeGrid;

class NodeGridItem {
    
    USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
    NodeGridItem(NodeProxy<EngineUiDomain>* node, NodeGrid& nodeGrid);

    NodeProxy<EngineUiDomain>* node;

    VarSignalT<float> x;
    VarSignalT<float> y;
    void setPos(float x, float y);

    VarSignalT<bool> selected;
    void setSelected(bool selected);

private:
    NodeGrid& nodeGrid;

    friend class GridItemCoordinator;

};
