#include "observer.h"

#include <iterator>

void Observer::observe(Observable *o)
{
  o->registerObserver(this);
}

void Observable::registerObserver(Observer *o)
{
  observers.push_back(o);
}

void Observable::notifyObservers(/*TODO PASSING FORMAT*/)
{
  for (auto obs : observers) {
    obs->notify();
  }
}
