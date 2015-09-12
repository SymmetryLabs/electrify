#pragma once
#include "BlueprintUiGlobals.h"

#include <observable_vector.h>
#include <observes.h>
#include <var.h>

#include "SelectionContainer.h"

class NodeSignal;
class CompoundNodeHandle;
class NodeGridWire;
class NodeGridSocket;
class NodeGridItem;
class NodeGridItemSocket;
class NodeGridItemNode;

class NodeGrid : Observes, public SelectionContainer {

public:
    explicit NodeGrid(CompoundNodeHandle& compoundNode);

    CompoundNodeHandle& compoundNode;

    void addNode(string name, float x, float y);
    void removeNode(NodeGridItemNode& gridItem);
    
    void removeWire(NodeGridWire& gridWire);

    ObservableVector<shared_ptr<NodeGridItemNode>> gridItems;
    ObservableVector<shared_ptr<NodeGridWire>> gridWires;
    ObservableVector<shared_ptr<NodeGridItemSocket>> gridOutputs;
    
    NodeGridSocket* gridSocketForNodeSignal(NodeSignal& nodeSignal);
    
    Var<shared_ptr<NodeGridWire>> draggingWire;
    void draggingWireStarted(NodeGridSocket& socket);
    void draggingWireMoved(Point<int> p);
    void draggingWireEnded(NodeGridSocket* socket = nullptr);

private:
    
    Var<NodeGridItem*> selectedGridItem;

};
