#pragma once
#include "globals.h"

#include "signals.h"

struct ContextModifierChain;
template <typename V>
struct SignalFunction;

class BaseSocket {
public:
    explicit BaseSocket(type_index type_) : type(type_) {}
    virtual ~BaseSocket() = default;

    operator BaseSignal() const;

    virtual bool hasSignal() const = 0;
    virtual bool acceptsSignal(const BaseSignal& signal) const;
    virtual void setSignal(BaseSignal* signal) = 0;
    void addContextModifier(ContextModifierChain& contextModifierChain);
    void removeContextModifier(ContextModifierChain& contextModifierChain);

    const type_index type;

protected:
    ContextModifierChain* contextModifierChain = nullptr;

private:
    ENABLE_TYPE_ERASURE_ABSTRACT();

};

template <typename V>
class Socket : public BaseSocket, public SignalX<V> {

public:
    explicit Socket(V defaultValue_) : BaseSocket(typeid(V)), defaultValue(ConstantSignal<V>(defaultValue_)) {}
    Socket() : BaseSocket(typeid(V)) {}
    virtual ~Socket() = default;

    virtual void setSignal(BaseSignal* signal) override;
    virtual void setSignal(SignalX<V>* signal);
    virtual bool hasSignal() const override;
    virtual V calculate(const FrameContext& frame) const override;

protected:
    ConstantSignal<V> defaultValue;

private:
    SignalX<V>* signal = nullptr;

    ENABLE_TYPE_ERASURE();

};

template <typename V>
class ProxySocket : public Socket<V> {

public:
    explicit ProxySocket(SignalX<V>** signalAddr_) : signalAddr(signalAddr_) {}
    ProxySocket(SignalFunction<V>* signalFunctionAddr_, V defaultValue)
        :Socket<V>(defaultValue)
        ,signalFunctionAddr(signalFunctionAddr_) { setSignal(nullptr); }
    virtual ~ProxySocket() = default;

    virtual void setSignal(SignalX<V>* signal) override;

private:
    SignalX<V>** signalAddr = nullptr;
    SignalFunction<V>* signalFunctionAddr = nullptr;

    ENABLE_TYPE_ERASURE();

};

template <typename V>
struct SignalFunction {
    SignalFunction() = default;
    explicit SignalFunction(SignalX<V>* signal_) : signal(signal_) {}
    const V operator()(const FrameContext& frame) const { return signal->calculate(frame); }
private:
    SignalX<V>* signal = nullptr;

};

struct ContextModifierChain {

    explicit ContextModifierChain(function<FrameContext (const FrameContext& frame)> contextModifierFunction_)
        : contextModifierFunction(contextModifierFunction_) {}

    function<FrameContext (const FrameContext& frame)> contextModifierFunction;
    ContextModifierChain* nextModifierNode = nullptr;

    FrameContext modifyContext(const FrameContext& frame);

};

#include "socket.hpp"
