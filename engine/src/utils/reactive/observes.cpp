#include "observes.h"

#include <utility>

#include "observer.h"

ScopedObserver Observes::addObserver(Observer&& observer)
{
    auto so = ScopedObserver(std::forward<Observer>(observer));
    observers.push_back(so);
    return so;
}

ScopedObserver Observes::addScopedObserver(const ScopedObserver& scopedObserver)
{
    observers.push_back(scopedObserver);
    return scopedObserver;
}
