template<typename Domain>
void Observes<Domain>::addObserver(Observer<Domain>&& observer)
{
  observers.push_back(ScopedObserver<Domain>(move(observer)));
}

template<typename Domain>
template <typename FIn, typename S>
void Observes<Domain>::observeWithStart(const Signal<Domain, S>& subject, FIn&& func)
{
  func(subject.Value());
  addObserver(Observe(subject, forward<FIn>(func)));
}

template<typename Domain>
template <typename FIn>
void Observes<Domain>::observeWithStart(const Events<Domain, Token>& subject, FIn&& func)
{
  func(Token());
  addObserver(Observe(subject, forward<FIn>(func)));
}

template<typename Domain>
template <typename FIn, typename S>
void Observes<Domain>::observeWithCapture(const Signal<Domain, S>& subject, FIn&& func)
{
  addObserver(Observe(subject, forward<FIn>(func)));
}

template<typename Domain>
template <typename FIn, typename E>
void Observes<Domain>::observeWithCapture(const Events<Domain, E>& subject, FIn&& func)
{
  addObserver(Observe(subject, forward<FIn>(func)));
}
