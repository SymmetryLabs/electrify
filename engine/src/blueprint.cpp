#include "blueprint.h"

Color Blueprint::render(const FragmentContext& frag)
{
  return outputSocket.calculate(frag);
}
