#pragma once
#include "globals.h"

#include "signals.h"

struct ContextModifierChain;

class BaseSocket {
public:
    explicit BaseSocket(type_index type_) : type(type_) {}
    virtual ~BaseSocket() {}

    operator BaseSignal() const;

    virtual bool hasSignal() const = 0;
    virtual bool acceptsSignal(const BaseSignal& signal) const;
    virtual void setSignal(BaseSignal* signal) = 0;
    void addContextModifier(ContextModifierChain& contextModifierChain);
    void removeContextModifier(ContextModifierChain& contextModifierChain);

    const type_index type;

protected:
    ContextModifierChain* contextModifierChain = nullptr;

};

template <typename V>
class Socket : public BaseSocket, public SignalX<V> {

public:
    explicit Socket(V defaultValue_) : BaseSocket(typeid(V)), defaultValue(ConstantSignal<V>(defaultValue_)) {}
    Socket() : BaseSocket(typeid(V)) {}
    virtual ~Socket() {}

    virtual void setSignal(BaseSignal* signal) override;
    virtual void setSignal(SignalX<V>* signal);
    virtual bool hasSignal() const override;
    virtual V calculate(const FrameContext& frame) const override;

protected:
    ConstantSignal<V> defaultValue;

private:
    SignalX<V>* signal = nullptr;

};

template <typename V>
class ProxySocket : public Socket<V> {

public:
    explicit ProxySocket(SignalX<V>** signalAddr_) : signalAddr(signalAddr_) {}
    ProxySocket(SignalFunction<V>* signalFunctionAddr_, V defaultValue)
        :Socket<V>(defaultValue)
        ,signalFunctionAddr(signalFunctionAddr_) { setSignal(nullptr); }
    virtual ~ProxySocket() {}

    virtual void setSignal(SignalX<V>* signal) override;

private:
    SignalX<V>** signalAddr = nullptr;
    SignalFunction<V>* signalFunctionAddr = nullptr;

};

struct ContextModifierChain {

    explicit ContextModifierChain(function<FrameContext (const FrameContext& frame)> contextModifierFunction_)
        : contextModifierFunction(contextModifierFunction_) {}

    function<FrameContext (const FrameContext& frame)> contextModifierFunction;
    ContextModifierChain* nextModifierNode = nullptr;

    FrameContext modifyContext(const FrameContext& frame);
};

#include "socket.tpp"
