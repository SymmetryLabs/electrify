template<typename Domain>
Observes<Domain>::~Observes()
{
  for (auto& observer : observers) {
    observer.Detach();
  }
}
