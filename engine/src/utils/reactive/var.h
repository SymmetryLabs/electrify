#pragma once

#include <tuple>
#include <utility>

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "observable.h"
#include "type_traits_ext.h"
#include "token_source.h"
#include "event.h"

template<typename T>
class Var : protected boost::base_from_member<rxcpp::subjects::replay<T, rxcpp::identity_one_worker>>, public TokenSource<T> {

public:
    Var();
    Var(const T& f);
    Var(T&& f);

    Var(const Var<T>& other) = default;
    Var(Var<T>&& other);

    virtual ~Var();

    bool hasValue() const;
    T getValue() const;

    void emit(const T& value) override;
    void emit(T&& value) override;

    void removeValue();

    void operator()(const T& value);
    void operator()(T&& value);

    Var& operator<<=(const T& value);
    Var& operator<<=(T&& value);

    operator T() const;

    Observable<T> withoutStart() const;

    Observable<T> previous() const;

    Observable<std::tuple<T, T>> pairWithPrevious() const;
    template<typename Fn>
    Observer observeWithPrevious(const Fn& fn) const;

    Var<T>& operator=(const Var<T>& other) = default;
    Var<T>& operator=(Var<T>&& other);

    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type = 0>
    auto operator=(const T2& b)
        -> typename Check<decltype(std::declval<T&>() = b), Var<T>&>::type;
    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type = 0>
    auto operator=(T2&& b)
        -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), Var<T>&>::type;

    template <typename T2>
    auto operator+=(const T2& b)
        -> typename Check<decltype(std::declval<T&>() += b), Var<T>&>::type
    {
        T value = getValue();
        value += b;
        this->emit(std::move(value));
        return *this;
    }

protected:
    void preEmit() const;

private:
    Event<T> notifyPrevious;

};

#include "var.hpp"
