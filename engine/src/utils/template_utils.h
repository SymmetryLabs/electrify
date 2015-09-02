#pragma once

template<typename T>
struct inner_template {
    typedef T type;
};

template<template<typename> class O, typename T>
struct inner_template<O<T>> {
    typedef T type;
};

// http://stackoverflow.com/a/25748937/216311
struct VoidNoOp {
    void operator()() const { };
    template<typename P1, typename... Params>
    void operator()(P1 p1, Params... parameters) const {
        (void)(p1);             // we do this just to remove warnings -- requires the recursion
        operator()(parameters...);
    }
};
