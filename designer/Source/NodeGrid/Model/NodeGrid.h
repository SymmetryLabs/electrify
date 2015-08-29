#pragma once
#include "BlueprintUiGlobals.h"

#include <compound_node.h>
#include <observable_vector.h>
#include <node.h>
#include <observes.h>

#include "NodeGridItem.h"
#include "NodeGridWire.h"
#include "SelectionContainer.h"

class NodeGrid : Observes, public SelectionContainer {

public:
    explicit NodeGrid(CompoundNodeProxy* compoundNode);

    CompoundNodeProxy* compoundNode;

    void addNode(string name, float x, float y);
    void removeNode(NodeGridItem& gridItem);
    NodeGridItem* nodeWithUuid(boost::uuids::uuid uuid);
    
    void removeWire(NodeGridWire& gridWire);

    ObservableVector<shared_ptr<NodeGridItem>> gridItems;
    ObservableVector<shared_ptr<NodeGridWire>> gridWires;
    
    NodeGridSocket* gridSocketForNodeSignal(NodeSignalProxy& nodeSignal);
    
    Var<shared_ptr<NodeGridWire>> draggingWire;
    void draggingWireStarted(NodeGridItem& gridItemStart, NodeGridSocket& socket);
    void draggingWireMoved(Point<int> p);
    void draggingWireEnded(NodeGridItem& gridItemEnd, NodeGridSocket& socket);

private:
    
    Var<NodeGridItem*> selectedGridItem;

};
