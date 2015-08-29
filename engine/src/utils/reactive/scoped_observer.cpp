#include "scoped_observer.h"

ScopedObserver::ScopedObserver(Observer&& observer)
: container(std::make_shared<ScopedObserverContainer>(std::forward<Observer>(observer)))
{
}

ScopedObserver::ScopedObserverContainer::ScopedObserverContainer(Observer&& observer)
: Observer(std::move(observer))
{
}

ScopedObserver::ScopedObserverContainer::~ScopedObserverContainer()
{
    unsubscribe();
}
