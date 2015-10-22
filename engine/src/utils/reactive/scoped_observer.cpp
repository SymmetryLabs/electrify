#include "scoped_observer.h"

ScopedObserver::ScopedObserver(Observer&& observer)
: container(std::make_shared<ScopedObserverContainer>(std::forward<Observer>(observer)))
{
}

void ScopedObserver::release()
{
    if (container) {
        container->unsubscribe();
        container = nullptr;
    }
}

ScopedObserver::ScopedObserverContainer::ScopedObserverContainer(Observer&& observer)
: Observer(std::move(observer))
{
}

ScopedObserver::ScopedObserverContainer::~ScopedObserverContainer()
{
    unsubscribe();
}
