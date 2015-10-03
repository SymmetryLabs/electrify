#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

template<typename Input>
class Incrementer : public BasicNode<Skip<Input, 1>, Color> {

public:
    static void configure(Incrementer<Input>& node, NodeHandle& handle);
    
    virtual void init() override;
    virtual void update(const FrameContext& frame) override;

    Color calculate(const FrameContext& frame) const override;

private:
    Def<Input, 0, Color> colorInput;
    
    int increment = 0;

};

#include "incrementer.hpp"
