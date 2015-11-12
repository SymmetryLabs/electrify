#pragma once

#include <utility>
#include <vector>

#include "scoped_observer.h"

template <typename T>
class Observable;
class Observer;

class Observes {

public:
    virtual ~Observes() = default;

    ScopedObserver addObserver(Observer&& observer);
    ScopedObserver addScopedObserver(const ScopedObserver& scopedObserver);

    template <typename FIn, typename T>
    ScopedObserver scopedObserve(const Observable<T>& subject, FIn&& func);

    template <typename FIn, typename T>
    ScopedObserver doubleScopedObserve(Observable<T>& subject, FIn&& func);

private:
    std::vector<ScopedObserver> observers;

};

#include "observes.hpp"
