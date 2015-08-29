#include "observes.h"

#include <utility>

void Observes::addObserver(Observer&& observer)
{
    observers.push_back(ScopedObserver(std::forward<Observer>(observer)));
}
