#pragma once
#include "constants.h"

#include "fragment_context.h"

class Renderable {

public:
  Renderable() {}
  virtual ~Renderable() {}

  virtual Color render(const FragmentContext& fragmentContext) =0;

};
