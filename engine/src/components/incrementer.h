#pragma once
#include "globals.h"

#include "basic_component.h"

class Incrementer : public BasicComponent<Color> {

public:
  Incrementer();
  
  virtual void init();
  virtual void update(const FrameContext& frame) override;

  Color calculate(const FragmentContext& frag) const override;

private:
  SignalFunction<Color> colorInput;
  
  int increment = 0;

};
