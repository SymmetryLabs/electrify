#pragma once

#include <boost/utility/base_from_member.hpp>
#include <rxcpp/rx.hpp>

#include "token_source.h"

template<typename T = void*>
class Event : protected boost::base_from_member<rxcpp::subjects::subject<T>>, public TokenSource<T> {

public:
    Event();

    Event(const Event<T>& other) = default;
    Event(Event<T>&& other);

    Event<T>& operator=(const Event<T>& other) = default;
    Event<T>& operator=(Event<T>&& other);

    void operator()() const;
    
    void operator()(const T& value) const;
    void operator()(T&& value) const;

    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type = 0>
    auto operator=(const T2& b)
        -> typename Check<decltype(std::declval<TokenSource<T>&>() = b), Event<T>&>::type;
    template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type = 0>
    auto operator=(T2&& b)
        -> typename Check<decltype(std::declval<TokenSource<T>&>() = std::forward<T2>(b)), Event<T>&>::type;

private:
    rxcpp::subjects::subject<T> subject;

};

#include "event.hpp"
