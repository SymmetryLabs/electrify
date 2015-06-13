#pragma once
#include "constants.h"

#include "component.h"

class ColorDoubler : public Component {

public:
  ColorDoubler();

  Color doubleColor(const FragmentContext& frag);

private:
  Signal<Color>* colorInput;

};
