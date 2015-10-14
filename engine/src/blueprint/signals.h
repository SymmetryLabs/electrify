#pragma once
#include "globals.h"

#include "frame_context.h"

class BaseSignal {
public:
    explicit BaseSignal(type_index type_) : type(type_) {}
    virtual ~BaseSignal() = default;

    const type_index type;

private:
    ENABLE_TYPE_ERASURE_BASE();
};

template<typename V>
class SignalX : public BaseSignal {
public:
    SignalX() : BaseSignal(typeid(V)) {}
    virtual ~SignalX() = default;

    virtual V calculate(const FrameContext& frame) const = 0;

private:
    ENABLE_TYPE_ERASURE_ABSTRACT();

};

template<typename V>
class FunctionSignal : public SignalX<V> {
public:
    explicit FunctionSignal(function<V(const FrameContext& frame) const> calculate_function_)
        : calculate_function(calculate_function_)
    {}

    template<typename C>
    FunctionSignal(V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst)
        : calculate_function(bind(mem_fn(calculate_function_), &inst, placeholders::_1))
    {}
    virtual ~FunctionSignal() = default;

    virtual V calculate(const FrameContext& frame) const override;
    function<V(const FrameContext& frame)> calculate_function;

private:
    ENABLE_TYPE_ERASURE();

};

template<typename V>
class ConstantSignal : public SignalX<V> {
public:
    ConstantSignal() = default;
    explicit ConstantSignal(const V value_) : value(value_) {}
    virtual ~ConstantSignal() = default;

    virtual V calculate(const FrameContext& frame) const override;

private:
    const V value;

    ENABLE_TYPE_ERASURE();

};

#include "signals.hpp"
