#pragma once
#include "globals.h"

#include "basic_component.h"

template <typename V>
class TranslateComponent : BasicComponent<V> {

public:
  TranslateComponent();

  V calculate(const FrameContext& frame) const override;

private:
  SignalFunction<V> signalInput;

  SignalFunction<double> translateX;
  SignalFunction<double> translateY;
  SignalFunction<double> translateZ;

};

typedef TranslateComponent<Color> TranslateColorComponent;

#include "translate_component.tpp"
