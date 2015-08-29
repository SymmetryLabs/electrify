#include <utility>

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
T Var<T>::getValue() const
{
    return this->member.get_value();
}
