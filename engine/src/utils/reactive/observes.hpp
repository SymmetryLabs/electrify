#include <utility>

template<typename FIn, typename T>
ScopedObserver Observes::scopedObserve(const Observable<T>& subject, FIn&& func)
{
    return addObserver(subject.observe(std::forward<FIn>(func)));
}
