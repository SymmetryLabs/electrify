#pragma once
#include "BlueprintUiGlobals.h"

#include <compound_node.h>
#include <observable_vector.h>
#include <node.h>
#include <observes.h>

#include "NodeGridItem.h"
#include "NodeGridWire.h"
#include "NodeGridCoordinator.h"

class NodeGrid : Observes<EngineUiDomain> {
    
    USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
    explicit NodeGrid(CompoundNodeProxy<EngineUiDomain>* compoundNode);

    CompoundNodeProxy<EngineUiDomain>* compoundNode;
    
    NodeGridCoordinator nodeGridCoordinator;

    void addNode(string name, float x, float y);
    void removeNode();
    NodeGridItem* nodeWithUuid(boost::uuids::uuid uuid);
    
    void deselectAllNodes();
    void setSelectedNode(NodeGridItem& gridItem, bool selected);

    ObservableVector<EngineUiDomain, shared_ptr<NodeGridItem>> gridItems;
    ObservableVector<EngineUiDomain, shared_ptr<NodeGridWire>> gridWires;

private:
    
    VarSignal<EngineUiDomain, NodeGridItem*> selectedGridItem = MakeVar<EngineUiDomain, NodeGridItem*>(nullptr);

    NodeGridItem* addGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);
    shared_ptr<NodeGridItem> removeGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);

    NodeGridWire* addGridWireWith(size_t pos, NodeWire& wire);
    shared_ptr<NodeGridWire> removeGridWireWith(size_t pos, NodeWire wire);

};
