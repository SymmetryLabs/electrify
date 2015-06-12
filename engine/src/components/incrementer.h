#pragma once
#include "constants.h"

#include "component.h"

class Incrementer : public Component {

public:
  Incrementer();
  
  void update(const FrameContext& frame) override;
  Color increment_color(const FragmentContext& frag);

private:
  Socket<Color>* colorSocket;
  
  int _increment = 0;

};