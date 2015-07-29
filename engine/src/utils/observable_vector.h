#pragma once
#include "globals.h"

#include "data_proxy.h"
#include "observes.h"

template<typename D, typename T, typename MasterDomain = D>
class ObservableVector : public Observes<MasterDomain> {

public:

  EventSource<D, pair<size_t, reference_wrapper<T>>> valueAdded = MakeEventSource<D, pair<size_t, reference_wrapper<T>>>();
  EventSource<D, pair<size_t, T>> valueRemoved = MakeEventSource<D, pair<size_t, T>>();

  typename vector<T>::reference operator[] (typename vector<T>::size_type n) { return v[n]; }
  typename vector<T>::const_reference operator[] (typename vector<T>::size_type n) const { return v[n]; }

  typename vector<T>::reference at(typename vector<T>::size_type pos) { return v.at(pos); }
  typename vector<T>::const_reference at(typename vector<T>::size_type pos) const { return v.at(pos); }

  typename vector<T>::reference front() { return v.front(); }
  typename vector<T>::const_reference front() const { return v.front(); }

  typename vector<T>::reference back() { return v.back(); }
  typename vector<T>::const_reference back() const { return v.back(); }

  typename vector<T>::iterator begin() { return v.begin(); }
  typename vector<T>::const_iterator begin() const { return v.begin(); }
  typename vector<T>::const_iterator cbegin() const { return v.cbegin(); }

  typename vector<T>::iterator end() { return v.end(); }
  typename vector<T>::const_iterator end() const { return v.end(); }
  typename vector<T>::const_iterator cend() const { return v.cend(); }

  typename vector<T>::size_type size() const { return v.size(); }

  void clear();

  typename vector<T>::iterator insert(typename vector<T>::const_iterator pos, const T& value);
  typename vector<T>::iterator insert(typename vector<T>::const_iterator pos, T&& value);

  typename vector<T>::iterator erase(typename vector<T>::iterator pos);
  typename vector<T>::iterator erase(typename vector<T>::const_iterator pos);

  void push_back(const T& value);
  void push_back(T&& value);

  void pop_back();

  template<typename SlaveDomain, typename SlaveType>
  void makeProxySlave(ObservableVector<SlaveDomain, shared_ptr<SlaveType>, D>& slave, ProxyBridge& proxyBridge);

  Events<MasterDomain, pair<size_t, T>> masterAddedValueEvent;
  Events<MasterDomain, pair<size_t, T>> masterRemovedValueEvent;

private:
  vector<T> v;

};

#include "observable_vector.tpp"
