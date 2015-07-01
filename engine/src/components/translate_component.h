#pragma once
#include "globals.h"

#include "context_modifier_component.h"

class TranslateComponent : public ContextModifierComponent {

public:
  TranslateComponent();

  FrameContext modifyContext(const FrameContext& original) override;

private:
  SignalFunction<float> translateX;
  SignalFunction<float> translateY;
  SignalFunction<float> translateZ;

};
