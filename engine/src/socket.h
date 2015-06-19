#pragma once
#include "globals.h"

#include "signals.h"

class BaseSocket {
public:
  BaseSocket(type_index type_) : type(type_) {}
  virtual ~BaseSocket() {}

  virtual bool hasSignal() = 0;

  const type_index type;
};

template <typename V>
class Socket : public BaseSocket, public Signal<V> {

public:
  Socket(V defaultValue_) : BaseSocket(typeid(V)), defaultValue(ConstantSignal<V>(defaultValue_)) {}
  Socket() : BaseSocket(typeid(V)) {}
  virtual ~Socket() {}

  virtual void setSignal(Signal<V>* signal_);
  virtual bool hasSignal() override;
  virtual V calculate(const FragmentContext& frag) const override;

protected:
  ConstantSignal<V> defaultValue;

private:
  Signal<V>* signal = nullptr;

};

template <typename V>
class ProxySocket : public Socket<V> {

public:
  ProxySocket(Signal<V>** signalAddr_) : signalAddr(signalAddr_) {}
  ProxySocket(SignalFunction<V>* signalFunctionAddr_, V defaultValue)
    :Socket<V>(defaultValue)
    ,signalFunctionAddr(signalFunctionAddr_) { setSignal(nullptr); }
  virtual ~ProxySocket() {}

  virtual void setSignal(Signal<V>* signal) override;

private:
  Signal<V>** signalAddr = nullptr;
  SignalFunction<V>* signalFunctionAddr = nullptr;

};

#include "socket.tpp"
