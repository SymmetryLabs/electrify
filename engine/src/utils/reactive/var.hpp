template <typename T>
Var<T>::Var()
: boost::base_from_member<rxcpp::subjects::replay<T, rxcpp::identity_one_worker>>(
    rxcpp::subjects::replay<T, rxcpp::identity_one_worker>(1, rxcpp::identity_current_thread()))
, TokenSource<T>(this->member.get_subscriber(), this->member.get_observable())
{
}

template <typename T>
Var<T>::Var(const T& f)
: Var()
{
    this->member.get_subscriber().on_next(f);
}

template <typename T>
Var<T>::Var(T&& f)
: Var()
{
    this->member.get_subscriber().on_next(std::move(f));
}

template <typename T>
Var<T>::Var(Var<T>&& other)
: Var()
{
    *this = std::move(other);
}

template <typename T>
Var<T>::~Var()
{
    ObjectOwner::clear();
}

template <typename T>
bool Var<T>::hasValue() const
{
    return !this->member.get_values().empty();
}

template <typename T>
T Var<T>::getValue() const
{
    auto vals = this->member.get_values();
    return vals.empty() ? T() : vals.front();
}

template <typename T>
void Var<T>::removeValue()
{
    preEmit();
    this->member.clear_values();
}

template <typename T>
void Var<T>::emit(const T& value)
{
    preEmit();
    this->member.get_subscriber().on_next(value);
}

template <typename T>
void Var<T>::emit(T&& value)
{
    preEmit();
    this->member.get_subscriber().on_next(std::forward<T>(value));
}

template <typename T>
void Var<T>::operator()(const T& value)
{
    emit(value);
}

template <typename T>
void Var<T>::operator()(T&& value)
{
    emit(std::forward<T>(value));
}

template <typename T>
Var<T>& Var<T>::operator<<=(const T& value)
{
    emit(value);
    return *this;
}

template <typename T>
Var<T>& Var<T>::operator<<=(T&& value)
{
    emit(std::forward<T>(value));
    return *this;
}

template <typename T>
Var<T>::operator T() const
{
    return getValue();
}

template <typename T>
Observable<T> Var<T>::withoutStart() const
{
    return Observable<T>(this->member.get_nonreplay_observable());
}

template <typename T>
Observable<T> Var<T>::previous() const
{
    return notifyPrevious;
}

template <typename T>
Observable<std::tuple<T, T>> Var<T>::pairWithPrevious() const
{
    return Observable<std::tuple<T, T>>(rxcpp::observable<>::just<T>(T()).concat(this->observable).zip(this->observable));
}

template <typename T>
template <typename Fn>
Observer Var<T>::observeWithPrevious(const Fn& fn) const
{
    return pairWithPrevious().observe([fn] (const std::tuple<T, T>& pair) {
        fn(std::get<0>(pair), std::get<1>(pair));
    });
}

template <typename T>
Var<T>& Var<T>::operator=(Var<T>&& other)
{
    boost::base_from_member<rxcpp::subjects::replay<T, rxcpp::identity_one_worker>>::operator=(std::move(other));
    Observable<T>::operator=(std::move(other));
    notifyPrevious.operator=(std::move(other.notifyPrevious));

    this->fixRxObjects(this->member.get_subscriber(), this->member.get_observable());

    other.member = rxcpp::subjects::replay<T, rxcpp::identity_one_worker>(1, rxcpp::identity_current_thread());
    other.fixRxObjects(other.member.get_subscriber(), other.member.get_observable());

    return *this;
}

template <typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type>
auto Var<T>::operator=(const T2& b)
    -> typename Check<decltype(std::declval<T&>() = b), Var<T>&>::type
{
    this->emit(b);
    return *this;
}

template <typename T>
template <typename T2, typename std::enable_if<!std::is_same<typename std::decay<T2>::type, Var<T>>::value, int>::type>
auto Var<T>::operator=(T2&& b)
    -> typename Check<decltype(std::declval<T&>() = std::forward<T2>(b)), Var<T>&>::type
{
    this->emit(std::forward<T2>(b));
    return *this;
}

template <typename T>
void Var<T>::preEmit() const
{
    if (hasValue()) {
        notifyPrevious(getValue());
    }
}
