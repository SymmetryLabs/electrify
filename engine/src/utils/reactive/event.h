#pragma once

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"

template <typename T = void*>
class Event : protected boost::base_from_member<rxcpp::subjects::subject<T>>, public TokenSource<T> {

public:
    Event();

    Event(const Event<T>& other) = default;
    Event(Event<T>&& other);

    void emit(const T& value) const;
    void emit(T&& value) const;

    void operator()() const;

    void operator()(const T& value) const;
    void operator()(T&& value) const;

    const Event& operator<<(const T& value) const;
    const Event& operator<<(T&& value) const;

    Event<T>& operator=(const Event<T>& other) = default;
    Event<T>& operator=(Event<T>&& other);

    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type = 0>
    auto operator=(const T2& b)
        -> typename Check<decltype(std::declval<T&>() = b), Event<T>&>::type;
    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type = 0>
    auto operator=(T2&& b)
        -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), Event<T>&>::type;

};

#include "event.hpp"
