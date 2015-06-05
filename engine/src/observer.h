#pragma once

#include <vector>

class Observable;

class Observer
{
  public:
  virtual void notify(/*TODO PASSING FORMAT*/) = 0;
  void observe(Observable *o);
};

class Observable
{
  private:
    std::vector<Observer*> observers;
  public:
      void registerObserver(Observer *o);
      void notifyObservers(/*TODO PASSING FORMAT*/);
};

