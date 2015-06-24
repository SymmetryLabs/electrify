#pragma once
#include "globals.h"

#include "basic_component.h"

class ColorDoubler : public BasicComponent<Color> {

public:
  ColorDoubler();

  Color calculate(const FrameContext& frame) const override;

private:
  SignalFunction<Color> colorInput;

};
