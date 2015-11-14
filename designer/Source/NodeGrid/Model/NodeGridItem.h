#pragma once
#include "BlueprintUiGlobals.h"

#include <node.h>

#include "Selectable.h"

class NodeGrid;
class NodeGridSocket;

class NodeGridItem : public Selectable {

public:
    NodeGridItem(DataTransmitter& gridItemProxy, NodeGrid& NodeGrid);
    virtual ~NodeGridItem() = default;
    
    void init();
    
    DataTransmitter& gridItemProxy;
    NodeGrid& nodeGrid;
    
    bool containsNodeGridSocket(const NodeGridSocket& nodeGridSocket) const;
    ObservableVector<shared_ptr<NodeGridSocket>> inputs;
    ObservableVector<shared_ptr<NodeGridSocket>> outputs;
    
    NodeGridSocket* gridSocketForNodeSignal(const NodeSignal& nodeSignal) const;

    Var<float> x;
    Var<float> y;
    void setPos(float x, float y);
    
    virtual string getName() const = 0;
    virtual string getId() const = 0;

};
