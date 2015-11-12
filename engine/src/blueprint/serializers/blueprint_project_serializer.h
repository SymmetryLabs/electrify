#pragma once
#include "globals.h"

#include <cereal/cereal.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include "blueprint_project.h"

#include "project_class_serializer.h"
#include "blueprint_serializer.h"

template <typename Archive>
void serialize(Archive& archive, BlueprintProject& project)
{
    archive(
        cereal::make_nvp("Project", cereal::base_class<Project>(&project)),
        cereal::make_nvp("blueprint", project.blueprint)
    );
}
