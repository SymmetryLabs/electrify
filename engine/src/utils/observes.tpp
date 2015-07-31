template<typename Domain>
Observes<Domain>::~Observes()
{
  for (auto& observer : observers) {
    observer.Detach();
  }
}

template<typename Domain>
void Observes<Domain>::addObserver(Observer<Domain>&& observer)
{
  observers.push_back(move(observer));
}

template<typename Domain>
template <typename FIn, typename S>
void Observes<Domain>::observeWithStart(const Signal<Domain, S>& subject, FIn&& func)
{
  addObserver(Observe(subject, forward<FIn>(func)));
  func(subject.Value());
}
