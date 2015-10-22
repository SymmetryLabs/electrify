#pragma once

#include <rxcpp/rx.hpp>

#include "observable.h"
#include "type_traits_ext.h"

template<typename T>
class TokenSource : public Observable<T> {

public:
    TokenSource(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable);
    virtual ~TokenSource() = default;

    void emit(const T& value) const;
    void emit(T&& value) const;

    void operator()(const T& value) const;
    void operator()(T&& value) const;

    const TokenSource& operator<<(const T& value) const;
    const TokenSource& operator<<(T&& value) const;

    template <typename T2, typename std::enable_if<
        !std::is_base_of<typename std::decay<T2>::type, TokenSource<T>>::value
        && !std::is_base_of<TokenSource<T>, typename std::decay<T2>::type>::value, int>::type = 0>
    auto operator=(const T2& b)
        -> typename Check<decltype(std::declval<T&>() = b), TokenSource<T>&>::type;
    template <typename T2, typename std::enable_if<
        !std::is_base_of<typename std::decay<T2>::type, TokenSource<T>>::value
        && !std::is_base_of<TokenSource<T>, typename std::decay<T2>::type>::value, int>::type = 0>
    auto operator=(T2&& b)
        -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), TokenSource<T>&>::type;

protected:
    rxcpp::subscriber<T> subscriber;

    void fixRxObjects(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable);

};

#include "token_source.hpp"
