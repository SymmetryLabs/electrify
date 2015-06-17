#pragma once
#include "constants.h"

#include "basic_component.h"

class ConstantColorComponent : public BasicComponent<Color> {

public:
  Color calculate(const FragmentContext& frag) const override;

};
