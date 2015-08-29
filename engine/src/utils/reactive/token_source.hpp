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
