#pragma once
#include "globals.h"

#include "basic_component.h"

class ScalarTransform : public BasicComponent<float> {

public:
  ScalarTransform();
  virtual ~ScalarTransform() {}

  SignalFunction<float> input;

};
