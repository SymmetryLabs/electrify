#include <utility>

template<typename FIn, typename T>
void Observes::observe(const Observable<T>& subject, FIn&& func)
{
    addObserver(subject.observe(std::forward<FIn>(func)));
}
