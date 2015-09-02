/*
  ==============================================================================

    NodeGridSocket.h
    Created: 24 Aug 2015 6:57:27pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include <node_signal.h>

class NodeGrid;

enum struct NodeGridSocketDirection { INPUT, OUTPUT };

class NodeGridSocket {
    
public:
    NodeGridSocket(NodeSignalProxy& nodeSignal, NodeGrid& nodeGrid, const NodeGridSocketDirection& direction);
    
    NodeSignalProxy& nodeSignal;
    
    NodeGrid& nodeGrid;
    
    NodeGridSocketDirection direction;
    
};
