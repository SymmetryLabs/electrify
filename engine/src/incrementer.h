#pragma once
#include "component.h"
#include "color.h"
#include "frame_context.h"

class Incrementer : public Component
{
  private:
   int _increment = 0;
  public:
   Incrementer();
   ~Incrementer();
   void update(FrameContext *f);
   Color* increment_color(FrameContext *f);
};