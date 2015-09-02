#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

#include "Selectable.h"
#include "NodeGridSocket.h"

class NodeGrid;

class NodeGridItem : public Selectable {

public:
    NodeGridItem(NodeGrid& NodeGrid);
    
    NodeGrid& nodeGrid;
    
    bool containsNodeGridSocket(const NodeGridSocket& nodeGridSocket) const;
    ObservableVector<shared_ptr<NodeGridSocket>> inputs;
    ObservableVector<shared_ptr<NodeGridSocket>> outputs;
    
    NodeGridSocket* gridSocketForNodeSignal(const NodeSignalProxy& nodeSignal) const;

    Var<float> x;
    Var<float> y;
    void setPos(float x, float y);
    
    virtual string getName() const = 0;

};
