#pragma once
#include "globals.h"

#include "basic_node.h"

class Incrementer : public BasicNode<Color> {

public:
    Incrementer();

    static const string nodeName() { return "Incrementer"; }
    
    virtual void init();
    virtual void update(const FrameContext& frame) override;

    Color calculate(const FrameContext& frame) const override;

private:
    SignalFunction<Color> colorInput;
    
    int increment = 0;

};
