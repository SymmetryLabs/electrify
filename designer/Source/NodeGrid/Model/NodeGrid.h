#pragma once
#include "BlueprintUiGlobals.h"

#include <compound_node.h>
#include <observable_vector.h>
#include <node.h>
#include <observes.h>

#include "NodeGridItem.h"
#include "NodeGridWire.h"
#include "SelectionContainer.h"
#include "NodeGridItemNode.h"
#include "NodeGridItemSocket.h"

class NodeGrid : Observes, public SelectionContainer {

public:
    explicit NodeGrid(CompoundNodeProxy* compoundNode);

    CompoundNodeProxy* compoundNode;

    void addNode(string name, float x, float y);
    void removeNode(NodeGridItemNode& gridItem);
    
    void removeWire(NodeGridWire& gridWire);

    ObservableVector<shared_ptr<NodeGridItemNode>> gridItems;
    ObservableVector<shared_ptr<NodeGridWire>> gridWires;
    ObservableVector<shared_ptr<NodeGridItemSocket>> gridOutputs;
    
    NodeGridSocket* gridSocketForNodeSignal(NodeSignalProxy& nodeSignal);
    
    Var<shared_ptr<NodeGridWire>> draggingWire;
    void draggingWireStarted(NodeGridSocket& socket);
    void draggingWireMoved(Point<int> p);
    void draggingWireEnded(NodeGridSocket* socket = nullptr);

private:
    
    Var<NodeGridItem*> selectedGridItem;

};
