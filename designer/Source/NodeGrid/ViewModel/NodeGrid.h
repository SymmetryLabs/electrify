#pragma once
#include "BlueprintUiGlobals.h"

#include <compound_node.h>
#include <observable_vector.h>
#include <node.h>
#include <observes.h>

#include "BlueprintUiObject.h"
#include "NodeGridItem.h"
#include "NodeGridWire.h"

class NodeGrid : public BlueprintUiObject, Observes<EngineUiDomain> {

public:
    explicit NodeGrid(CompoundNodeProxy<EngineUiDomain>* compoundNode);

    CompoundNodeProxy<EngineUiDomain>* compoundNode;

    void addNode(string name, float x, float y);
    void removeNode();
    NodeGridItem* nodeWithUuid(boost::uuids::uuid uuid);
    
    void deselectAllNodes();
    void setSelectedNode(NodeGridItem& gridItem, bool selected);

    ObservableVector<EngineUiDomain, shared_ptr<NodeGridItem>> gridItems;
    ObservableVector<EngineUiDomain, shared_ptr<NodeGridWire>> gridWires;
    
    VarSignalT<shared_ptr<NodeGridWire>> draggingWire;
    void draggingWireStarted(NodeGridItem& gridItemStart, string signalName);
    void draggingWireMoved(Point<int> p);
    void draggingWireEnded(NodeGridItem& gridItemEnd, string signalName);

private:
    
    VarSignal<EngineUiDomain, NodeGridItem*> selectedGridItem = MakeVar<EngineUiDomain, NodeGridItem*>(nullptr);

    NodeGridItem* addGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);
    shared_ptr<NodeGridItem> removeGridItemWith(size_t pos, NodeProxy<EngineUiDomain>& node);

    NodeGridWire* addGridWireWith(size_t pos, NodeWire& wire);
    shared_ptr<NodeGridWire> removeGridWireWith(size_t pos, NodeWire wire);

};
