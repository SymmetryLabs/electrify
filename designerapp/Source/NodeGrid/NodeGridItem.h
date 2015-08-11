#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

#include "BlueprintUiObject.h"
#include "GridItemCoordinator.h"

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
