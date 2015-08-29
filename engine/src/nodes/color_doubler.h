#pragma once
#include "globals.h"

#include "basic_node.h"

class ColorDoubler : public BasicNode<Color> {

public:
    ColorDoubler();

    Color calculate(const FrameContext& frame) const override;

private:
    SignalFunction<Color> colorInput;

};
