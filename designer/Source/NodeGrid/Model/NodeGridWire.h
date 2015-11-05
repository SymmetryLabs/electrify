#pragma once
#include "BlueprintUiGlobals.h"

#include <var.h>

#include "Selectable.h"

class NodeWire;
class NodeGrid;
class NodeGridSocket;

class NodeGridWire : public Selectable {

public:
    NodeGridWire(NodeWire& nodeWire, NodeGrid& nodeGrid, NodeGridSocket* emittingGridSocket, NodeGridSocket* receivingGridSocket);
    NodeGridWire(NodeGrid& nodeGrid, NodeGridSocket* emittingGridSocket, NodeGridSocket* receivingGridSocket = nullptr);
    virtual ~NodeGridWire() = default;

    NodeWire* nodeWire;

    NodeGridSocket* emittingGridSocket;
    NodeGridSocket* receivingGridSocket;
    
    Var<Point<int>> emittingPos;
    Var<Point<int>> receivingPos;
    
    void setOtherPosition(Point<int> pos);
    
    void deleteSelectable() override;
    
private:
    NodeGrid& nodeGrid;

};
