#pragma once
#include "constants.h"

class BaseParameter {
public:
  BaseParameter(type_index type_) : type(type_) {}
  virtual ~BaseParameter() {}

  const type_index type;
};

template <typename V>
class Parameter : public BaseParameter {

public:
  virtual ~Parameter() {}
  Parameter() : BaseParameter(typeid(V)) {}

};
