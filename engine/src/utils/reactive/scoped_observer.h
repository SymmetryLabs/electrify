#pragma once

#include "observer.h"

class ScopedObserver {

public:
    explicit ScopedObserver(Observer&& observer);

private:

    struct ScopedObserverContainer : Observer {
        explicit ScopedObserverContainer(Observer&& observer);
        ~ScopedObserverContainer();
    };
    
    std::shared_ptr<ScopedObserverContainer> container;

};
