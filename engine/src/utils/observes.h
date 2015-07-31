#pragma once
#include "globals.h"

template<typename Domain>
class Observes {

public:
  virtual ~Observes();

  void addObserver(Observer<Domain>&& observer);

  template <typename FIn, typename S>
  void observeWithStart(const Signal<Domain, S>& subject, FIn&& func);

private:
  vector<Observer<Domain>> observers;

};

#include "observes.tpp"
