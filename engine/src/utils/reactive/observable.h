#pragma once

#include <type_traits>

#include <rxcpp/rx.hpp>

#include "template_utils.h"
#include "observer.h"

template<typename T, typename S>
struct has_return_type {
    typedef S type;
};

template<typename T>
struct has_return_type<T, typename T::return_type> {
};

template<typename T>
class Observable {

protected:
    rxcpp::observable<T> observable;

public:
    Observable();
    explicit Observable(const rxcpp::observable<T>& observable);
    virtual ~Observable() {}

    typedef T type;

    template<typename... ArgN>
    Observer observe(ArgN&&... an) const;

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
