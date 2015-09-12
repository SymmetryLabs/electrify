/*
  ==============================================================================

    NodeGridItemSocket.h
    Created: 1 Sep 2015 4:42:25pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include "NodeGridItem.h"

class NodeSocket;
class NodeGrid;

class NodeGridItemSocket : public NodeGridItem {
    
public:
    NodeGridItemSocket(NodeSocket& nodeSocket, NodeGrid& nodeGrid);
    
    NodeSocket& nodeSocket;
    
    string getName() const override;
    
    void deleteSelectable() override;
};
