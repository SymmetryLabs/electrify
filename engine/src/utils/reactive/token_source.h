#pragma once

#include <rxcpp/rx.hpp>

#include "observable.h"
#include "type_traits_ext.h"

template <typename T>
class TokenSource : public Observable<T> {

public:
    TokenSource(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable);
    virtual ~TokenSource() = default;

    virtual void emit(const T& value);
    virtual void emit(T&& value);

protected:
    rxcpp::subscriber<T> subscriber;

    void fixRxObjects(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable);

};

#include "token_source.hpp"
