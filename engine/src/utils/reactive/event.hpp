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
    TokenSource<T>::operator=(std::move(other));

    this->fixRxObjects(this->member.get_subscriber(), this->member.get_observable());

    other.member = rxcpp::subjects::subject<T>();
    other.fixRxObjects(other.member.get_subscriber(), other.member.get_observable());

    return *this;
}

template<typename T>
void Event<T>::operator()(const T& value) const
{
    TokenSource<T>::template operator()(value);
}

template<typename T>
void Event<T>::operator()(T&& value) const
{
    TokenSource<T>::template operator()(std::forward<T>(value));
}

template<typename T>
void Event<T>::operator()() const
{
    TokenSource<T>::operator()(nullptr);
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type>
auto Event<T>::operator=(const T2& b)
    -> typename Check<decltype(std::declval<TokenSource<T>&>() = b), Event<T>&>::type
{
    TokenSource<T>::operator=(b);
    return *this;
}

template<typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Event<T>>::value, int>::type>
auto Event<T>::operator=(T2&& b)
    -> typename Check<decltype(std::declval<TokenSource<T>&>() = std::forward<T2>(b)), Event<T>&>::type
{
    TokenSource<T>::operator=(std::forward<T2>(b));
    return *this;
}
