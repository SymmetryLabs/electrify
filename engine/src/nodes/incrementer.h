#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

class Incrementer : public BasicNode<Color> {

public:
    explicit Incrementer(NodeHandle& nodeHandle);
    
    virtual void init();
    virtual void update(const FrameContext& frame) override;

    Color calculate(const FrameContext& frame) const override;

private:
    SignalFunction<Color> colorInput;
    
    int increment = 0;

};
