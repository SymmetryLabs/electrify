#pragma once
#include "globals.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>

#include "node_handle.h"

#include "var_serializer.h"

template <typename Archive>
void save(Archive& archive, const NodeHandle& handle)
{ 
    archive(
        cereal::make_nvp("nodeName", handle.nodeName),
        cereal::make_nvp("name", handle.name)
    );
}

template <typename Archive>
void load(Archive& archive, NodeHandle& handle)
{
    archive(
        cereal::make_nvp("nodeName", handle.nodeName)
    );
    handle.postCtor();
    archive(
        cereal::make_nvp("name", handle.name)
    );
}

namespace cereal
{
    template <class T> inline
    typename std::enable_if<std::is_base_of<NodeHandle, T>::value, void>::type
    epilogue(JSONInputArchive& ar, const std::shared_ptr<T>& t )
    {
        ar.finishNode();
        t->postSharedPtrConstruction();
    }

    template <class T> inline
    typename std::enable_if<std::is_base_of<NodeHandle, T>::value, void>::type
    epilogue(JSONInputArchive& ar, const std::weak_ptr<T>& t)
    {
        ar.finishNode();
        t->postSharedPtrConstruction();
    }
}
