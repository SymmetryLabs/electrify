#pragma once
#include "BlueprintUiGlobals.h"

#include <node_wire.h>
#include <node_socket.h>

#include "Selectable.h"
#include "NodeGridItem.h"
#include "NodeGridSocket.h"

class NodeGrid;

class NodeGridWire : public Selectable {

public:
    NodeGridWire(NodeWireProxy& nodeWire, NodeGrid& nodeGrid, NodeGridSocket* emittingGridSocket, NodeGridSocket* receivingGridSocket);
    NodeGridWire(NodeGrid& nodeGrid, NodeGridSocket* emittingGridSocket, NodeGridSocket* receivingGridSocket = nullptr);

    NodeWireProxy* nodeWire;

    NodeGridSocket* emittingGridSocket;
    NodeGridSocket* receivingGridSocket;
    
    Var<Point<int>> emittingPos;
    Var<Point<int>> receivingPos;
    
    void setOtherPosition(Point<int> pos);
    
    void deleteSelectable() override;
    
private:
    NodeGrid& nodeGrid;

};
