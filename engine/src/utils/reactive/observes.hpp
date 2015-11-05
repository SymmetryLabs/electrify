template<typename FIn, typename T>
ScopedObserver Observes::scopedObserve(const Observable<T>& subject, FIn&& func)
{
    return addObserver(subject.observe(std::forward<FIn>(func)));
}

template<typename FIn, typename T>
ScopedObserver Observes::doubleScopedObserve(Observable<T>& subject, FIn&& func)
{
    return addScopedObserver(subject.scopedObserve(subject, std::forward<FIn>(func)).fork());
}
