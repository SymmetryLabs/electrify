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
