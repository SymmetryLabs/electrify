#pragma once
#include "globals.h"

#include "frame_context.h"

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

  virtual V calculate(const FrameContext& frame) const = 0;
};

template <typename V>
class FunctionSignal : public Signal<V> {
public:
  FunctionSignal(function<V (const FrameContext& frame) const> calculate_function_)
    :calculate_function(calculate_function_)
  {}

  template <typename C>
  FunctionSignal(V (C::* calculate_function_)(const FrameContext& frame) const, void* inst)
    :calculate_function(bind(mem_fn(calculate_function_), (C*)inst, placeholders::_1))
  {}
  virtual ~FunctionSignal() {}

  virtual V calculate(const FrameContext& frame) const override;
  function<V (const FrameContext& frame)> calculate_function;
};

template <typename V>
class ConstantSignal : public Signal<V> {
public:
  ConstantSignal() {}
  ConstantSignal(const V value_) : value(value_) {}
  virtual ~ConstantSignal() {}

  virtual V calculate(const FrameContext& frame) const override;

private:
  const V value;

};


template <typename V>
struct SignalFunction {
  SignalFunction() {}
  SignalFunction(Signal<V>* signal_) : signal(signal_) {}
  const V operator()(const FrameContext& frame) const { return signal->calculate(frame); }
private:
  Signal<V>* signal = nullptr;
};

#include "signals.tpp"
