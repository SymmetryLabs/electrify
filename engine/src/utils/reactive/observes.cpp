#include "observes.h"

#include <utility>

#include "observer.h"

ScopedObserver Observes::addObserver(Observer&& observer)
{
    auto so = ScopedObserver(std::forward<Observer>(observer));
    observers.push_back(so);
    return so;
}
