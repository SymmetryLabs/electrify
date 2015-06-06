    #include "component.h"
#include "color.h"
#include "frame_context.h"
class SquareWave : public Component
{
  private:
    double _value = 0;
  public:
    SquareWave();
    ~SquareWave();
    double* calculate_value(FrameContext *f);

};
