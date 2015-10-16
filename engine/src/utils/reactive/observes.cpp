#include "observes.h"

#include <utility>

#include "observer.h"

void Observes::addObserver(Observer&& observer)
{
    observers.push_back(ScopedObserver(std::forward<Observer>(observer)));
}
