#pragma once
#include "globals.h"

#include "signals.h"

class BaseParameter {
public:
    BaseParameter(type_index type_) : type(type_) {}
    virtual ~BaseParameter() {}

    const type_index type;
};

template <typename V>
class Parameter : public BaseParameter, public SignalX<V> {

public:
    Parameter() : BaseParameter(typeid(V)) {}
    virtual ~Parameter() {}

};

template <typename V>
class ValueParameter : public Parameter<V> {

public:
    virtual ~ValueParameter() {}

    virtual V calculate(const FrameContext& frame) override;

private:
    V value;

};

#include "parameter.tpp"
