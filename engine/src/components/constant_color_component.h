#pragma once
#include "constants.h"

#include "component.h"
#include "color.h"
#include "frame_context.h"

class ConstantColorComponent : public Component
{
  public:
    ConstantColorComponent();
    Color calculate_color(__attribute__((unused)) FrameContext f) {return Color(255);};
};