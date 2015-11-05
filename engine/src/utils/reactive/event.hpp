#include <utility>

template<typename T>
Event<T>::Event()
: boost::base_from_member<rxcpp::subjects::subject<T>>()
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable())
{
}

template<typename T>
Event<T>::Event(Event<T>&& other)
: Event()
{
    *this = std::move(other);
}

template<typename T>
Event<T>& Event<T>::operator=(Event<T>&& other)
{
    boost::base_from_member<rxcpp::subjects::subject<T>>::operator=(std::move(other));
    Observable<T>::operator=(std::move(other));

    this->fixRxObjects(this->member.get_subscriber(), this->member.get_observable());

    other.member = rxcpp::subjects::subject<T>();
    other.fixRxObjects(other.member.get_subscriber(), other.member.get_observable());

    return *this;
}

template<typename T>
void Event<T>::emit(const T& value) const
{
    this->member.get_subscriber().on_next(value);
}

template<typename T>
void Event<T>::emit(T&& value) const
{
    this->member.get_subscriber().on_next(std::forward<T>(value));
}

template<typename T>
void Event<T>::operator()() const
{
    this->operator()(nullptr);
}

template<typename T>
void Event<T>::operator()(const T& value) const
{
    emit(value);
}

template<typename T>
void Event<T>::operator()(T&& value) const
{
    emit(std::forward<T>(value));
}

template<typename T>
const Event<T>& Event<T>::operator<<(const T& value) const
{
    emit(value);
    return *this;
}

template<typename T>
const Event<T>& Event<T>::operator<<(T&& value) const
{
    emit(std::forward<T>(value));
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type>
auto Event<T>::operator=(const T2& b)
    -> typename Check<decltype(std::declval<T&>() = b), Event<T>&>::type
{
    this->emit(b);
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type>
auto Event<T>::operator=(T2&& b)
    -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), Event<T>&>::type
{
    this->emit(std::forward<T2>(b));
    return *this;
}
