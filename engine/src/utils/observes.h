#pragma once
#include "globals.h"

template<typename Domain>
class Observes {

public:
    void addObserver(Observer<Domain>&& observer);

    template <typename FIn, typename S>
    void observeWithStart(const Signal<Domain, S>& subject, FIn&& func);
    template <typename FIn>
    void observeWithStart(const Events<Domain>& subject, FIn&& func);

    template <typename FIn, typename S>
    void observeWithCapture(const Signal<Domain, S>& subject, FIn&& func);
    template <typename FIn, typename E>
    void observeWithCapture(const Events<Domain, E>& subject, FIn&& func);

private:
    vector<ScopedObserver<Domain>> observers;

};

#include "observes.tpp"
