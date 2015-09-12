#pragma once
#include "globals.h"

#include "basic_node.h"
#include "color.h"

class ColorDoubler : public BasicNode<Color> {

public:
    explicit ColorDoubler(NodeHandle& nodeHandle);

    Color calculate(const FrameContext& frame) const override;

private:
    SignalFunction<Color> colorInput;

};
