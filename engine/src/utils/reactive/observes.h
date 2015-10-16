#pragma once

#include <vector>

#include "scoped_observer.h"
#include "observable.h"
#include "observer.h"

class Observes {

public:
    virtual ~Observes() = default;

    void addObserver(Observer&& observer);

    template<typename FIn, typename T>
    void scopedObserve(const Observable<T>& subject, FIn&& func);

private:
    std::vector<ScopedObserver> observers;

};

#include "observes.hpp"
