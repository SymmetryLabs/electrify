#include "component.h"
#include "color.h"
#include "frame_context.h"

class ConstantColorComponent : public Component
{
  public:
    ConstantColorComponent();
    Color calculate_color(FrameContext f) {return Color(255);};
};