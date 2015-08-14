/*
  ==============================================================================

    NodeGridCoordinator.cpp
    Created: 12 Aug 2015 4:43:41pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridCoordinator.h"

NodeGridCoordinator::NodeGridCoordinator(CompoundNodeProxy<EngineUiDomain>* compoundNode)
: draggingWire(MakeVar<EngineUiDomain, shared_ptr<NodeGridWire>>(nullptr))
, compoundNode(compoundNode)
{
    
}

void NodeGridCoordinator::draggingWireStarted(NodeGridItem& nodeGridItem, const NodeSocket& socket)
{
    draggingWire <<= make_shared<NodeGridWire>(&nodeGridItem, socket);
}

void NodeGridCoordinator::draggingWireMoved(Point<int> p)
{
    if (draggingWire.Value()) {
        draggingWire.Value()->setOtherPosition(p);
    }
}

void NodeGridCoordinator::draggingWireEnded(NodeGridItem& gridItemEnd, const NodeSocket& socket)
{
    if (draggingWire.Value()) {
        compoundNode->wireSubnodes(draggingWire.Value()->emittingSocket, socket);
        draggingWire <<= nullptr;
    }
}
