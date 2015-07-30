#pragma once
#include "globals.h"

template<typename Domain>
class Observes {

public:
  virtual ~Observes();

  void addObserver(Observer<Domain>&& observer);

private:
  vector<Observer<Domain>> observers;

};

#include "observes.tpp"
