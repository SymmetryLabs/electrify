#pragma once

#include <utility>

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"
#include "type_traits_ext.h"

template<typename T>
class Var : protected boost::base_from_member<rxcpp::subjects::behavior<T>>, public TokenSource<T> {

public:
    Var();
    Var(const T& f);
    Var(T&& f);

    Var(const Var<T>& other) = default;
    Var(Var<T>&& other);

    T getValue() const;

    operator T() const;

    Var<T>& operator=(const Var<T>& other) = default;
    Var<T>& operator=(Var<T>&& other);

    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type = 0>
    auto operator=(const T2& b)
        -> typename Check<decltype(std::declval<TokenSource<T>&>() = b), Var<T>&>::type;
    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type = 0>
    auto operator=(T2&& b)
        -> typename Check<decltype(std::declval<TokenSource<T>&>() = std::forward<T2>(b)), Var<T>&>::type;

    template <typename T2>
    auto operator+=(const T2& b)
        -> typename Check<decltype(std::declval<T&>() += b), Var<T>&>::type
    {
        T value = getValue();
        value += b;
        this->emit(std::move(value));
        return *this;
    }

};

#include "var.hpp"
