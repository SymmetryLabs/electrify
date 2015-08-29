#pragma once

#include <rxcpp/rx.hpp>

#include "observable.h"

template<typename T>
class TokenSource : public Observable<T> {

public:
    TokenSource(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable);

    void emit(const T& value) const;
    void emit(T&& value) const;

    void operator()(const T& value) const;
    void operator()(T&& value) const;

    const TokenSource& operator<<(const T& value) const;
    const TokenSource& operator<<(T&& value) const;

protected:
    rxcpp::subscriber<T> subscriber;

};

#include "token_source.hpp"
