#pragma once
#include "constants.h"

#include "fragment_context.h"

class BaseSignal {
public:
  BaseSignal(type_index type_) : type(type_) {}

  const type_index type;
};

template <class V>
class Signal : public BaseSignal {
public:
  Signal(function<V (const FragmentContext& frag)> calculate_function_)
    :BaseSignal(typeid(V))
    ,calculate_function(calculate_function_)
  {
  }

  template <class C>
  Signal(V (C::* calculate_function_)(const FragmentContext& frag), void* inst)
    :BaseSignal(typeid(V))
    ,calculate_function(bind(mem_fn(calculate_function_), (C*)inst, placeholders::_1))
  {
  }

  V calculate(const FragmentContext& frag);
  function<V (const FragmentContext& frag)> calculate_function;
};

class BaseSocket {
public:
  BaseSocket(type_index type_) : type(type_) {}

  const type_index type;
};

template <class V>
class Socket : public BaseSocket {
public:
  Socket() : BaseSocket(typeid(V)) {}

  V calculate(const FragmentContext& frag);

  Signal<V>* signal;
};

#include "signal.tpp"
