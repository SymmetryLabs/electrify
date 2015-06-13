#pragma once
#include "constants.h"

#include "component.h"

class Incrementer : public Component {

public:
  Incrementer();
  
  virtual void init();
  virtual void update(const FrameContext& frame) override;

  Color incrementColor(const FragmentContext& frag);

private:
  Signal<Color>* colorInput;
  
  int increment;

};
