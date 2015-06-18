#pragma once
#include "globals.h"

#include "basic_component.h"

class ConstantColorComponent : public BasicComponent<Color> {

public:
  Color calculate(const FragmentContext& frag) const override;

};
