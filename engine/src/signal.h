#pragma once
#include "globals.h"

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

  virtual V calculate(const FragmentContext& frag) const = 0;
};

template <typename V>
class FunctionSignal : public Signal<V> {
public:
  FunctionSignal(function<V (const FragmentContext& frag) const> calculate_function_)
    :calculate_function(calculate_function_)
  {}

  template <typename C>
  FunctionSignal(V (C::* calculate_function_)(const FragmentContext& frag) const, void* inst)
    :calculate_function(bind(mem_fn(calculate_function_), (C*)inst, placeholders::_1))
  {}
  virtual ~FunctionSignal() {}

  virtual V calculate(const FragmentContext& frag) const override;
  function<V (const FragmentContext& frag)> calculate_function;
};

template <typename V>
class ConstantSignal : public Signal<V> {
public:
  ConstantSignal() {}
  ConstantSignal(const V value_) : value(value_) {}
  virtual ~ConstantSignal() {}

  virtual V calculate(const FragmentContext& frag) const override;

private:
  const V value;

};


template <typename V>
struct SignalFunction {
  SignalFunction() {}
  SignalFunction(Signal<V>* signal_) : signal(signal_) {}
  const V operator()(const FragmentContext& frag) const { return signal->calculate(frag); }
private:
  Signal<V>* signal = nullptr;
};

#include "signal.tpp"
