#pragma once
#include "constants.h"

#include "component.h"

class ColorDoubler : public Component {

public:
  ColorDoubler();
  Color double_color(const FragmentContext& frag);

private:
  Socket<Color>* colorSocket;

};
