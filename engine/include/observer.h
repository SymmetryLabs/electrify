#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observable;

class Observer
{
  public:
  void notify(/*TODO PASSING FORMAT*/) {};
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

#endif //OBSERVER_H