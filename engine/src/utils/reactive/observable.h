#pragma once

#include <tuple>
#include <type_traits>

#include <rxcpp/rx.hpp>

#include "template_utils.h"
#include "object_owner.h"
#include "observer.h"
#include "observes.h"
#include "object_owner.h"

template<typename T = void*>
class Observable : public Observes, public ObjectOwner {

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

    template <typename Fn>
    auto mapLatest(const Fn& fn) const
        -> Observable<typename std::decay<decltype(fn(std::declval<T>()))>::type::type>;

    auto ignore(T value) const
        -> Observable<T>;

    auto tokenize() const
        -> Observable<void*>;

protected:
    rxcpp::observable<T> observable;

    void fixRxObjects(const rxcpp::observable<T>& observable);

    template<typename t>
    friend class Observable;

};

#define LATEST_PROPERTY(obj, property)                                      \
    obj.mapLatest([] (std::decay<decltype(obj)>::type::type obj_)           \
            -> std::decay<decltype(obj_->property)>::type& {                \
        return obj_->property;                                              \
    })

#include "observable.hpp"
