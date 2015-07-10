#pragma once
#include "globals.h"

#include "context_modifier_component.h"

class TranslateComponent : public ContextModifierComponent {

public:
  TranslateComponent();

  static const string componentName() { return "Translate"; }

  FrameContext modifyContext(const FrameContext& original) override;

private:
  SignalFunction<float> translateX;
  SignalFunction<float> translateY;
  SignalFunction<float> translateZ;

};
