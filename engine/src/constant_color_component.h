#include "component.h"
#include "color.h"

class ConstantColorComponent : public Component
{
  public:
    Color* calculate_color(Pixel *pixel, Group *topLevel /*, frameContext */) {return new Color();};
    ConstantColorComponent();
};