#pragma once
#include "component.h"
class BaseSignal
{

};

template <class T> 
class Signal : public BaseSignal
{
  public:
    std::function<T (Pixel *pixel, Group *topLevel /*, frameContext */)> calculate_function;
};

template <class T> 
class InputSocket : public BaseSignal
{
  public:
    Signal<T> *input_signal;
};

