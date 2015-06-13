#pragma once
#include "constants.h"

#include "component.h"

class ConstantColorComponent : public Component {

public:
  ConstantColorComponent();

  Color calculateColor(__attribute__((unused)) const FragmentContext& frag);

};
