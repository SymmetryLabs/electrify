/*
  ==============================================================================

    NodeGridSocket.h
    Created: 24 Aug 2015 6:57:27pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

class NodeSignal;
class NodeGrid;

enum struct NodeGridSocketDirection { INPUT, OUTPUT };

class NodeGridSocket {
    
public:
    NodeGridSocket(NodeSignal& nodeSignal, NodeGrid& nodeGrid, const NodeGridSocketDirection& direction);
    
    NodeSignal& nodeSignal;
    
    NodeGrid& nodeGrid;
    
    NodeGridSocketDirection direction;
    
};
