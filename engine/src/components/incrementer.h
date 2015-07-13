#pragma once
#include "globals.h"

#include "basic_component.h"

class Incrementer : public BasicComponent<Color> {

public:
  Incrementer();

  static const string componentName() { return "Incrementer"; }
  
  virtual void init();
  virtual void update(const FrameContext& frame) override;

  Color calculate(const FrameContext& frame) const override;

private:
  SignalFunction<Color> colorInput;
  
  int increment = 0;

};
