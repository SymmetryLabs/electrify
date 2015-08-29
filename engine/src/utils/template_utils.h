#pragma once

template<typename T>
struct inner_template {
    typedef T type;
};

template<template<typename> class O, typename T>
struct inner_template<O<T>> {
    typedef T type;
};
