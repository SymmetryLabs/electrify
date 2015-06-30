#pragma once
#include "globals.h"

#include "context_modifier_component.h"

class TranslateComponent : public ContextModifierComponent {

public:
  TranslateComponent();

  FrameContext modifyContext(const FrameContext& original) override;

private:
  SignalFunction<double> translateX;
  SignalFunction<double> translateY;
  SignalFunction<double> translateZ;

};
