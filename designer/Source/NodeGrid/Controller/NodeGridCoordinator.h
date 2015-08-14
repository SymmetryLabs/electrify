/*
  ==============================================================================

    NodeGridCoordinator.h
    Created: 12 Aug 2015 4:43:41pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include <compound_node.h>
#include <node_socket.h>

#include "NodeGridWire.h"

class NodeGridCoordinator {
    
    USING_REACTIVE_DOMAIN(EngineUiDomain)

public:
    NodeGridCoordinator(CompoundNodeProxy<EngineUiDomain>* compoundNode);
    
    VarSignalT<shared_ptr<NodeGridWire>> draggingWire;
    void draggingWireStarted(NodeGridItem& gridItemStart, const NodeSocket& socket);
    void draggingWireMoved(Point<int> p);
    void draggingWireEnded(NodeGridItem& gridItemEnd, const NodeSocket& socket);
    
private:
    CompoundNodeProxy<EngineUiDomain>* compoundNode;
    
};
