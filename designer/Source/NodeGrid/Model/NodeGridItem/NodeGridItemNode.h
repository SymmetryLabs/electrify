/*
  ==============================================================================

    NodeGridItemNode.h
    Created: 1 Sep 2015 4:42:16pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

#include "NodeGridItem.h"

class NodeGrid;

class NodeGridItemNode : public NodeGridItem {

public:
    NodeGridItemNode(NodeHandle& node, NodeGrid& NodeGrid);
    
    NodeHandle& node;
    
    string getName() const override;
    string getId() const override;
    
    void deleteSelectable() override;
    
};
