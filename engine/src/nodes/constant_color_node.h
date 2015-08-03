#pragma once
#include "globals.h"

#include "basic_node.h"

class ConstantColorNode : public BasicNode<Color> {

  public:
    static const string nodeName() { return "Constant color"; }
  
    Color calculate(const FrameContext& frame) const override;
    Color color= Color(0xFF0000FF);
};
