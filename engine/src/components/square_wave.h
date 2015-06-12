#pragma once
#include "constants.h"

#include "component.h"

class SquareWave : public Component {

public:
  SquareWave();
  double calculate_value(const FragmentContext& frag);

};
