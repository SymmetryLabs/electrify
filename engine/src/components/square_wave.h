#pragma once
#include "constants.h"

#include "component.h"

class SquareWave : public Component {

public:
  SquareWave();

  double calculateValue(const FragmentContext& frag);

};
