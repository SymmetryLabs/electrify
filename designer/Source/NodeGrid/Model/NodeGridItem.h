#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

#include "Selectable.h"
#include "NodeGridSocket.h"

class NodeGrid;

class NodeGridItem : public Selectable {

public:
    NodeGridItem(NodeProxy& node, NodeGrid& NodeGrid);

    NodeProxy& node;
    
    NodeGrid& nodeGrid;
    
    ObservableVector<shared_ptr<NodeGridSocket>> inputs;
    ObservableVector<shared_ptr<NodeGridSocket>> outputs;
    
    NodeGridSocket* gridSocketForNodeSignal(NodeSignalProxy& nodeSignal);

    Var<float> x;
    Var<float> y;
    void setPos(float x, float y);
    
    void deleteSelectable() override;

};
