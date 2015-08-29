#include <utility>

template<typename T>
Event<T>::Event()
: boost::base_from_member<rxcpp::subjects::subject<T>>()
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable())
{
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
