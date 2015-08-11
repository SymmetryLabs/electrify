#pragma once
#include "blueprint_ui_globals.h"

#include "blueprint_ui_object.h"
#include "compound_node.h"
#include "node_grid_item.h"
#include "observable_vector.h"
#include "node.h"
#include "observes.h"
#include "grid_item_coordinator.h"
#include "node_grid_wire.h"

class NodeGrid : public BlueprintUiObject, Observes<EngineUiDomain> {

public:
    explicit NodeGrid(CompoundNodeProxy<EngineUiDomain>* compoundNode);

    CompoundNodeProxy<EngineUiDomain>* compoundNode;

    void addNode(string name, float x, float y);
    void removeNode();
    NodeGridItem* nodeWithUuid(boost::uuids::uuid uuid);

    ObservableVector<EngineUiDomain, shared_ptr<NodeGridItem>> gridItems;
    ObservableVector<EngineUiDomain, shared_ptr<NodeGridWire>> gridWires;

private:
    GridItemCoordinator gridItemCoordinator;

    NodeGridItem* addGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);
    shared_ptr<NodeGridItem> removeGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);

    NodeGridWire* addGridWireWith(size_t pos, NodeWire& wire);
    shared_ptr<NodeGridWire> removeGridWireWith(size_t pos, NodeWire wire);

};
