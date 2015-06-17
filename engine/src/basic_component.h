#pragma once
#include "constants.h"

#include "component.h"
#include "fragment_context.h"

template <typename V>
class BasicComponent : public Component {

public:
  virtual ~BasicComponent() {}
  BasicComponent();

  virtual V calculate(const FragmentContext& frag) const = 0;

};

#include "basic_component.tpp"
