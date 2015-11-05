#include "scoped_observer.h"

ScopedObserver::ScopedObserver(const Observer& observer)
: container(std::make_shared<ScopedObserverContainer>(observer))
{
}

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

ScopedObserver ScopedObserver::fork()
{
    return ScopedObserver{container->observer};
}

ScopedObserver::ScopedObserverContainer::ScopedObserverContainer(const Observer& observer_)
: observer(observer_)
{
}

ScopedObserver::ScopedObserverContainer::ScopedObserverContainer(Observer&& observer_)
: observer(std::move(observer_))
{
}

ScopedObserver::ScopedObserverContainer::~ScopedObserverContainer()
{
    unsubscribe();
}

void ScopedObserver::ScopedObserverContainer::unsubscribe()
{
    observer.unsubscribe();
}
