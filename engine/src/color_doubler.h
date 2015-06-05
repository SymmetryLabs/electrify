#include "component.h"
#include "color.h"

class ColorDoubler : public Component
{
  public:
   ColorDoubler();
   ~ColorDoubler();
   Color* double_color(Pixel *pixel, Group *topLevel /*, frameContext */);
};