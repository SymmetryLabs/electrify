#pragma once
#include "constants.h"

#include "component.h"
#include "signal.h"
#include "compound_component.h"
#include "renderable.h"

class Blueprint : public CompoundComponent, public Renderable {

public:
  Blueprint() {}
  virtual ~Blueprint() {}

  virtual Color render(const FragmentContext& frag) override;

  Socket<Color> outputSocket;

};
