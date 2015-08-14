#pragma once

#include "BlueprintUiGlobals.h"

#include <node_wire.h>
#include <node_socket.h>

#include "NodeGridItem.h"

class NodeGrid;

class NodeGridWire {
    
    USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
    NodeGridWire(NodeWire* nodeWire, NodeGrid& nodeGrid,
                 NodeGridItem* emittingGridItem, NodeGridItem* receivingGridItem);
    NodeGridWire(NodeGridItem* emittingGridItem, NodeSocket emittingSocket,
                 NodeGridItem* receivingGridItem = nullptr, NodeSocket receivingSocket = NodeSocket());

    NodeWire* nodeWire;

    NodeGridItem* emittingGridItem;
    NodeGridItem* receivingGridItem;
    
    NodeSocket emittingSocket;
    NodeSocket receivingSocket;
    
    VarSignalT<Point<int>> emittingPos;
    VarSignalT<Point<int>> receivingPos;
    
    void setOtherPosition(Point<int> pos);

};
