/*
  ==============================================================================

    NodeGridItemSocket.h
    Created: 1 Sep 2015 4:42:25pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include <node_socket.h>

#include "NodeGridItem.h"

class NodeGrid;

class NodeGridItemSocket : public NodeGridItem {
    
public:
    NodeGridItemSocket(NodeSocketProxy& nodeSocket, NodeGrid& nodeGrid);
    
    NodeSocketProxy& nodeSocket;
    
    string getName() const override;
    
    void deleteSelectable() override;
};
