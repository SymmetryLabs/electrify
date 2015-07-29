#pragma once
#include "globals.h"

template<typename Domain>
class Observes {

public:
  virtual ~Observes();

  vector<Observer<Domain>> observers;

};

#include "observes.tpp"
