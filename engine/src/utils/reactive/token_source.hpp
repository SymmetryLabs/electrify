template <typename T>
TokenSource<T>::TokenSource(const rxcpp::subscriber<T>& subscriber, const rxcpp::observable<T>& observable)
: Observable<T>(observable)
, subscriber(subscriber)
{
}

template <typename T>
void TokenSource<T>::emit(const T& value)
{
    subscriber.on_next(value);
}

template <typename T>
void TokenSource<T>::emit(T&& value)
{
    subscriber.on_next(std::forward<T>(value));
}

template <typename T>
void TokenSource<T>::fixRxObjects(const rxcpp::subscriber<T>& subscriber_, const rxcpp::observable<T>& observable)
{
    Observable<T>::fixRxObjects(observable);
    subscriber = subscriber_;
}
