#pragma once

#define ENABLE_TYPE_ERASURE_BASE()          \
template <typename, bool>                   \
friend class TypeErasureHelper;             \
virtual void raise() { throw this; }

#define ENABLE_TYPE_ERASURE()               \
template <typename, bool>                   \
friend class TypeErasureHelper;             \
virtual void raise() override               \
{ throw this; }

#define ENABLE_TYPE_ERASURE_ABSTRACT()      \
template <typename, bool>                   \
friend class TypeErasureHelper;             \
virtual void raise() = 0;

#define ENABLE_TYPE_ERASURE_NONVIRTUAL()    \
template <typename, bool>                   \
friend class TypeErasureHelper;             \
void raise() { throw this; }
