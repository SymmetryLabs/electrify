template<typename T>
Observable<T>::Observable()
: observable(rxcpp::observable<>::never<T>())
{
}

template<typename T>
Observable<T>::Observable(const rxcpp::observable<T>& observable)
: observable(observable)
{
}

template<typename T>
template<typename... ArgN>
typename std::enable_if<!std::is_convertible<
        typename std::tuple_element<0, std::tuple<ArgN...> >::type,
        std::function<void()>>::value,
    Observer>::type
Observable<T>::observe(ArgN&&... an) const
{
    return Observer(observable.subscribe(std::forward<ArgN>(an)...));
}

template<typename T>
template<typename Fn>
typename std::enable_if<
    std::is_convertible<Fn, std::function<void()>>::value,
    Observer>::type
Observable<T>::observe(const Fn& fn) const
{
    return Observer(observable.subscribe([fn] (T) {
        fn();
    }));
}

template<typename T>
template<typename Selector, typename R>
auto Observable<T>::map(Selector&& p) const
    -> Observable<R>
{
    return Observable<R>(observable.map(std::forward<Selector>(p)));
}

template<typename T>
template<class Value0, class... ValueN>
auto Observable<T>::merge(Value0 v0, ValueN... vn) const
    -> Observable<T>
{
    return Observable<T>(observable.merge(v0.observable, vn.observable...));
}

template<typename T>
auto Observable<T>::flattenLatest() const
    -> Observable<typename inner_template<T>::type>
{
    return Observable<T>(observable.switch_on_next());
}

template<typename T>
auto Observable<T>::ignore(T value) const
    -> Observable<T>
{
    return Observable<T>(observable.filter([=] (T t) {
        return t != value;
    }));
}

template<typename T>
auto Observable<T>::tokenize() const
    -> Observable<void*>
{
    return Observable<void*>(observable.map([=] (T t) -> void* {
        return nullptr;
    }));
}
