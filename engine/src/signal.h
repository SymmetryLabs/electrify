#pragma once
#include "constants.h"

#include "fragment_context.h"

class BaseSignal {
public:
  BaseSignal(type_index type_) : type(type_) {}
  virtual ~BaseSignal() {}

  const type_index type;
};

template <typename V>
class Signal : public BaseSignal {
public:
  Signal() : BaseSignal(typeid(V)) {}
  virtual ~Signal() {}

  virtual V calculate(const FragmentContext& frag) = 0;
};

template <typename V>
class FunctionSignal : public Signal<V> {
public:
  FunctionSignal(function<V (const FragmentContext& frag)> calculate_function_)
    :calculate_function(calculate_function_)
  {}

  template <typename C>
  FunctionSignal(V (C::* calculate_function_)(const FragmentContext& frag), void* inst)
    :calculate_function(bind(mem_fn(calculate_function_),
      (C*)inst, placeholders::_1))
  {}
  virtual ~FunctionSignal() {}

  virtual V calculate(const FragmentContext& frag) override;
  function<V (const FragmentContext& frag)> calculate_function;
};

#include "signal.tpp"
