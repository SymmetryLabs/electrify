#pragma once

#include <memory>
#include <tuple>
#include <vector>

#include "data_proxy.h"
#include "observes.h"
#include "template_utils.h"

template<typename T>
class ObservableVector : public Observes {

public:

    Event<std::pair<size_t, std::reference_wrapper<T>>> valueAdded;
    Event<std::pair<size_t, T>> valueRemoved;

    typename std::vector<T>::reference operator[] (typename std::vector<T>::size_type n) { return v[n]; }
    typename std::vector<T>::const_reference operator[] (typename std::vector<T>::size_type n) const { return v[n]; }

    typename std::vector<T>::reference at(typename std::vector<T>::size_type pos) { return v.at(pos); }
    typename std::vector<T>::const_reference at(typename std::vector<T>::size_type pos) const { return v.at(pos); }

    typename std::vector<T>::reference front() { return v.front(); }
    typename std::vector<T>::const_reference front() const { return v.front(); }

    typename std::vector<T>::reference back() { return v.back(); }
    typename std::vector<T>::const_reference back() const { return v.back(); }

    typename std::vector<T>::iterator begin() { return v.begin(); }
    typename std::vector<T>::const_iterator begin() const { return v.begin(); }
    typename std::vector<T>::const_iterator cbegin() const { return v.cbegin(); }

    typename std::vector<T>::iterator end() { return v.end(); }
    typename std::vector<T>::const_iterator end() const { return v.end(); }
    typename std::vector<T>::const_iterator cend() const { return v.cend(); }

    typename std::vector<T>::size_type size() const { return v.size(); }

    void clear();

    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, const T& value);
    typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator pos, T&& value);

    typename std::vector<T>::iterator erase(typename std::vector<T>::iterator pos);
    typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator pos);

    void push_back(const T& value);
    void push_back(T&& value);

    void pop_back();

    void makeProxySlave(ObservableVector<T>& slave, ProxyBridge& proxyBridge);

    template<typename SlaveType>
    void makeProxySlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ProxyBridge& proxyBridge);

    template<typename SlaveType, typename... ArgN>
    auto makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, ArgN&&... args)
        -> typename std::enable_if<!std::is_convertible<typename std::tuple_element<0, std::tuple<ArgN...> >::type, std::function<std::shared_ptr<SlaveType>(T)>>::value>::type;
    template<typename SlaveType, typename FCreate, typename FDestr = VoidNoOp>
    auto makeSlave(ObservableVector<std::shared_ptr<SlaveType>>& slave, FCreate&& createFunc, FDestr&& destructFunc = VoidNoOp())
        -> typename std::enable_if<std::is_convertible<FCreate, std::function<std::shared_ptr<SlaveType>(T)>>::value
                                    && std::is_convertible<FDestr, std::function<void(std::shared_ptr<SlaveType>)>>::value>::type;

private:
    std::vector<T> v;

};

#include "observable_vector.tpp"
