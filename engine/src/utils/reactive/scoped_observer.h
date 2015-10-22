#pragma once

#include "observer.h"

class ScopedObserver {

public:
    explicit ScopedObserver(Observer&& observer);

    void release();

private:

    struct ScopedObserverContainer : Observer {
        explicit ScopedObserverContainer(Observer&& observer);
        ~ScopedObserverContainer();
    };
    
    std::shared_ptr<ScopedObserverContainer> container;

};
