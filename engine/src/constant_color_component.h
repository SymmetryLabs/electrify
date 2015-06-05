#include "component.h"
#include "color.h"
#include "frame_context.h"

class ConstantColorComponent : public Component
{
  public:
    Color* calculate_color(FrameContext *f) {return new Color(255);};
    ConstantColorComponent();
};