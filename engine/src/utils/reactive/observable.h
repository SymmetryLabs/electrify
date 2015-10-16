#pragma once

#include <type_traits>

#include <rxcpp/rx.hpp>

#include "template_utils.h"
#include "observer.h"
#include "observes.h"

template<typename T = void*>
class Observable : public Observes {

protected:
    rxcpp::observable<T> observable;

public:
    Observable();
    explicit Observable(const rxcpp::observable<T>& observable);
    virtual ~Observable() = default;

    typedef T type;

    template<typename... ArgN>
    typename std::enable_if<!std::is_convertible<
            typename std::tuple_element<0, std::tuple<ArgN...> >::type,
            std::function<void()>>::value,
        Observer>::type
    observe(ArgN&&... an) const;

    template<typename Fn>
    typename std::enable_if<
        std::is_convertible<Fn, std::function<void()>>::value,
        Observer>::type
    observe(const Fn& fn) const;

    template<typename Selector, typename R = decltype(std::declval<Selector>()(std::declval<T>()))>
    auto map(Selector&& p) const
        -> Observable<R>;

    template<class Value0, class... ValueN>
    auto merge(Value0 v0, ValueN... vn) const
        -> Observable<T>;

    auto flattenLatest() const
        -> Observable<typename inner_template<T>::type>;

    auto ignore(T value) const
        -> Observable<T>;

    auto tokenize() const
        -> Observable<void*>;

};

#define LATEST_PROPERTY(obj, property)                          \
    obj.map([] (decltype(obj)::type obj_) {                     \
        return obj_->property;                                  \
    }).flattenLatest()

#include "observable.hpp"
