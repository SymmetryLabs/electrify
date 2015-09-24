#pragma once
#include "globals.h"

#include "frame_context.h"

class BaseSignal {
public:
    explicit BaseSignal(type_index type_) : type(type_) {}
    virtual ~BaseSignal() = default;

    const type_index type;
};

template<typename V>
class SignalX : public BaseSignal {
public:
    SignalX() : BaseSignal(typeid(V)) {}
    virtual ~SignalX() = default;

    virtual V calculate(const FrameContext& frame) const = 0;
};

template<typename V>
class FunctionSignal : public SignalX<V> {
public:
    explicit FunctionSignal(function<V(const FrameContext& frame) const> calculate_function_)
        : calculate_function(calculate_function_)
    {}

    template<typename C>
    FunctionSignal(V(C::* calculate_function_)(const FrameContext& frame) const, const C& inst)
        : calculate_function(std::bind(mem_fn(calculate_function_), &inst, placeholders::_1))
    {}
    virtual ~FunctionSignal() = default;

    virtual V calculate(const FrameContext& frame) const override;
    function<V(const FrameContext& frame)> calculate_function;
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

};

#include "signals.hpp"
