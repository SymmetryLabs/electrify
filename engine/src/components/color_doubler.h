#pragma once
#include "constants.h"

#include "basic_component.h"

class ColorDoubler : public BasicComponent<Color> {

public:
  ColorDoubler();

  Color calculate(const FragmentContext& frag) const override;

private:
  SignalFunction<Color> colorInput;

};
