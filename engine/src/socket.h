#pragma once
#include "constants.h"

#include "signal.h"

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
  Socket() : BaseSocket(typeid(V)) {}
  virtual ~Socket() {}

  virtual void setSignal(Signal<V>* signal_);
  virtual bool hasSignal() override;
  virtual V calculate(const FragmentContext& frag) override;

private:
  Signal<V>* signal;

};

template <typename V>
class ProxySocket : public Socket<V> {

public:
  ProxySocket(Signal<V>** signalAddr_) : signalAddr(signalAddr_) {}
  virtual ~ProxySocket() {}

  virtual void setSignal(Signal<V>* signal) override;

private:
  Signal<V>** signalAddr;

};

#include "socket.tpp"
