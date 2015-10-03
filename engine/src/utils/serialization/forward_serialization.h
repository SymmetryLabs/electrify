#pragma once

#include <cereal/archives/json.hpp>

#define FORWARD_SERIALIZATION(TYPE)                                     \
namespace cereal                                                        \
{                                                                       \
    inline void prologue(JSONOutputArchive& ar, const TYPE& t) {}       \
    inline void epilogue(JSONOutputArchive& ar, const TYPE& t) {}       \
    inline void prologue(JSONInputArchive& ar, const TYPE& t) {}        \
    inline void epilogue(JSONInputArchive& ar, const TYPE& t) {}        \
}

#define FORWARD_SERIALIZATION_TEMPLATE(TYPE)                            \
namespace cereal                                                        \
{                                                                       \
    template <typename T> inline                                        \
    void prologue(JSONOutputArchive& ar, const TYPE<T>& t) {}           \
    template <typename T> inline                                        \
    void epilogue(JSONOutputArchive& ar, const TYPE<T>& t) {}           \
    template <typename T> inline                                        \
    void prologue(JSONInputArchive& ar, const TYPE<T>& t) {}            \
    template <typename T> inline                                        \
    void epilogue(JSONInputArchive& ar, const TYPE<T>& t) {}            \
}   

#define FORWARD_SERIALIZATION_TEMPLATE_2(TYPE)                          \
namespace cereal                                                        \
{                                                                       \
    template <typename T0, typename T1> inline                          \
    void prologue(JSONOutputArchive& ar, const TYPE<T0, T1>& t) {}      \
    template <typename T0, typename T1> inline                          \
    void epilogue(JSONOutputArchive& ar, const TYPE<T0, T1>& t) {}      \
    template <typename T0, typename T1> inline                          \
    void prologue(JSONInputArchive& ar, const TYPE<T0, T1>& t) {}       \
    template <typename T0, typename T1> inline                          \
    void epilogue(JSONInputArchive& ar, const TYPE<T0, T1>& t) {}       \
}
