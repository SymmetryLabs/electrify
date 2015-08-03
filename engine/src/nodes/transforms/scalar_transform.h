#pragma once
#include "globals.h"

#include "basic_node.h"

class ScalarTransform : public BasicNode<float> {

public:
  ScalarTransform();
  virtual ~ScalarTransform() {}

  SignalFunction<float> input;

};
