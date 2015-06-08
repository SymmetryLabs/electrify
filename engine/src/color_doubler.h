#include "component.h"
#include "color.h"
#include "frame_context.h"

class ColorDoubler : public Component
{
  public:
   ColorDoubler();
   Color* double_color(FrameContext *f);
};