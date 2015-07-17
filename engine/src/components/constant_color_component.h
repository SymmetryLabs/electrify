#pragma once
#include "globals.h"

#include "basic_component.h"

class ConstantColorComponent : public BasicComponent<Color> {

  public:
    static const string componentName() { return "Constant color"; }
  
    Color calculate(const FrameContext& frame) const override;
    Color color= Color(0xFF0000FF);
};
