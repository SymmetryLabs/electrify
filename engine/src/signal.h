#pragma once
#include "component.h"
#include "frame_context.h"
class BaseSignal
{

};

template <class T> 
class Signal : public BaseSignal
{
  public:
    std::function<T (FrameContext f)> calculate_function;
};

template <class T> 
class InputSocket : public BaseSignal
{
  public:
    Signal<T> *input_signal;
};

