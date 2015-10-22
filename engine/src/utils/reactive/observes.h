#pragma once

#include <vector>

#include "scoped_observer.h"

template <typename T>
class Observable;
class Observer;

class Observes {

public:
    virtual ~Observes() = default;

    ScopedObserver addObserver(Observer&& observer);

    template<typename FIn, typename T>
    ScopedObserver scopedObserve(const Observable<T>& subject, FIn&& func);

private:
    std::vector<ScopedObserver> observers;

};

#include "observes.hpp"
