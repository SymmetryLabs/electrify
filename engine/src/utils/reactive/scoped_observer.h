#pragma once

#include "observer.h"

class ScopedObserver {

public:
    ScopedObserver() = default;
    explicit ScopedObserver(const Observer& observer);
    explicit ScopedObserver(Observer&& observer);

    void release();

    /*
     * forking creates another ScopedObserver such that
     * if either the original or the fork (or copies therein)
     * go out of scope, the subject Observer is unsubscribed.
     */
    ScopedObserver fork();

private:

    struct ScopedObserverContainer {
        explicit ScopedObserverContainer(const Observer& observer);
        explicit ScopedObserverContainer(Observer&& observer);
        ~ScopedObserverContainer();
        Observer observer;
        void unsubscribe();
    };
    
    std::shared_ptr<ScopedObserverContainer> container;

};
