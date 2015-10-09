#pragma once

#include <utility>

template <typename>
struct TestAccess {
    template <typename T, typename... Args>
    static void call(T& t, Args&&... args) {}
};

template <typename AnonType, typename T, typename... Args>
auto call(T& t, Args&&... args)
    -> decltype(TestAccess<AnonType>::template call<T>(t, std::forward<Args>(args)...)) {
    return TestAccess<AnonType>::template call<T>(t, std::forward<Args>(args)...);
}

template <typename AnonType, typename T>
auto access(T& t) -> decltype(TestAccess<AnonType>::template access<T>(t)) {
    return TestAccess<AnonType>::template access<T>(t);
}

#define DEF_ACCESS(NAME, FUNCTION_OR_VARIABLE)                      \
namespace { class NAME {}; }                                        \
template <>                                                         \
struct TestAccess<NAME> {                                           \
    template <typename T, typename... Args>                         \
    static auto call(T& t, Args&&... args)                          \
        -> decltype(t.FUNCTION_OR_VARIABLE(                         \
                std::forward<Args>(args)...)) {                     \
        return t.FUNCTION_OR_VARIABLE(                              \
            std::forward<Args>(args)...);                           \
    }                                                               \
    template <typename T>                                           \
    static auto access(T& t)                                        \
        -> decltype(t.FUNCTION_OR_VARIABLE) {                       \
        return t.FUNCTION_OR_VARIABLE;                              \
    }                                                               \
};
