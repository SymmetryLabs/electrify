#pragma once
#include "globals.h"

#include "basic_node.h"

class PixelXNode : public BasicNode<float> {

public:
  static const string nodeName() { return "Pixel.x"; }

  float calculate(const FrameContext& frame) const override;

};
