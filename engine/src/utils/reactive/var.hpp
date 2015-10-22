template<typename T>
Var<T>::Var()
: boost::base_from_member<rxcpp::subjects::behavior<T>>(rxcpp::subjects::behavior<T>(T()))
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable().skip(1))
{
}

template<typename T>
Var<T>::Var(const T& f)
: boost::base_from_member<rxcpp::subjects::behavior<T>>(rxcpp::subjects::behavior<T>(f))
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable())
{
}

template<typename T>
Var<T>::Var(T&& f)
: boost::base_from_member<rxcpp::subjects::behavior<T>>(rxcpp::subjects::behavior<T>(std::move(f)))
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable())
{
}

template<typename T>
Var<T>::Var(Var<T>&& other)
: Var()
{
    *this = std::move(other);
}

template<typename T>
T Var<T>::getValue() const
{
    return this->member.get_value();
}

template<typename T>
Var<T>::operator T() const
{
    return getValue();
}

template<typename T>
Var<T>& Var<T>::operator=(Var<T>&& other)
{
    bool skipped = true;
    {
        ScopedObserver(other.observe([&] (const T&) {
            skipped = false;
        }));
    }
    boost::base_from_member<rxcpp::subjects::behavior<T>>::operator=(std::move(other));
    TokenSource<T>::operator=(std::move(other));

    auto observable = this->member.get_observable();
    if (skipped) {
        observable = observable.skip(1);
    }
    this->fixRxObjects(this->member.get_subscriber(), observable);

    other.member = rxcpp::subjects::behavior<T>(T());
    other.fixRxObjects(other.member.get_subscriber(), other.member.get_observable().skip(1));

    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type>
auto Var<T>::operator=(const T2& b)
    -> typename Check<decltype(std::declval<TokenSource<T>&>() = b), Var<T>&>::type
{
    TokenSource<T>::operator=(b);
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type>
auto Var<T>::operator=(T2&& b)
    -> typename Check<decltype(std::declval<TokenSource<T>&>() = std::forward<T2>(b)), Var<T>&>::type
{
    TokenSource<T>::operator=(std::forward<T2>(b));
    return *this;
}
