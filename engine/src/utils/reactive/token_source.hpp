template<typename T>
TokenSource<T>::TokenSource(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable)
: Observable<T>(observable)
, subscriber(subscriber)
{
}

template<typename T>
void TokenSource<T>::emit(const T& value) const
{
    subscriber.on_next(value);
}

template<typename T>
void TokenSource<T>::emit(T&& value) const
{
    subscriber.on_next(std::forward<T>(value));
}

template<typename T>
void TokenSource<T>::operator()(const T& value) const
{
    emit(value);
}

template<typename T>
void TokenSource<T>::operator()(T&& value) const
{
    emit(std::forward<T>(value));
}

template<typename T>
const TokenSource<T>& TokenSource<T>::operator<<(const T& value) const
{
    emit(value);
    return *this;
}

template<typename T>
const TokenSource<T>& TokenSource<T>::operator<<(T&& value) const
{
    emit(std::forward<T>(value));
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<
        !std::is_base_of<typename std::decay<T2>::type, TokenSource<T>>::value
        && !std::is_base_of<TokenSource<T>, typename std::decay<T2>::type>::value, int>::type>
auto TokenSource<T>::operator=(const T2& b)
    -> typename Check<decltype(std::declval<T&>() = b), TokenSource<T>&>::type
{
    this->emit(b);
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<
        !std::is_base_of<typename std::decay<T2>::type, TokenSource<T>>::value
        && !std::is_base_of<TokenSource<T>, typename std::decay<T2>::type>::value, int>::type>
auto TokenSource<T>::operator=(T2&& b)
    -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), TokenSource<T>&>::type
{
    this->emit(std::forward<T2>(b));
    return *this;
}

template<typename T>
void TokenSource<T>::fixRxObjects(const rxcpp::subscriber<T>& subscriber_, const rxcpp::observable<T>& observable)
{
    Observable<T>::fixRxObjects(observable);
    subscriber = subscriber_;
}
