#pragma once

#define ENABLE_TYPE_ERASURE_BASE()          \
template <typename>                         \
friend class TypeErasureImpl;               \
virtual void raise()                        \
{                                           \
    throw this;                             \
}

#define ENABLE_TYPE_ERASURE()               \
template <typename>                         \
friend class TypeErasureImpl;               \
virtual void raise() override               \
{                                           \
    throw this;                             \
}

#define ENABLE_TYPE_ERASURE_ABSTRACT()      \
template <typename>                         \
friend class TypeErasureImpl;               \
virtual void raise() = 0;

#define ENABLE_TYPE_ERASURE_NONVIRTUAL()    \
template <typename>                         \
friend class TypeErasureImpl;               \
void raise()                                \
{                                           \
    throw this;                             \
}
