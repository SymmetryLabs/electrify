#pragma once
#include "globals.h"

#include "basic_node.h"

class ColorDoubler : public BasicNode<Color> {

public:
  ColorDoubler();

  static const string nodeName() { return "Color doubler"; }

  Color calculate(const FrameContext& frame) const override;

private:
  SignalFunction<Color> colorInput;

};
