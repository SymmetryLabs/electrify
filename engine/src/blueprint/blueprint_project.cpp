#include "blueprint_project.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

#include "blueprint.h"
#include "blueprint_project_serializer.h"

CEREAL_REGISTER_TYPE(BlueprintProject);

BlueprintProject::BlueprintProject(const shared_ptr<Blueprint>& blueprint_, unique_ptr<Model>&& model)
: Project(forward<unique_ptr<Model>>(model))
, blueprint(blueprint_)
{
}

Blueprint& BlueprintProject::getBlueprint() const
{
    return *blueprint;
}

unique_ptr<Renderable> BlueprintProject::releaseRenderable(DataBridge& dataBridge)
{
    return blueprint->releaseRenderable(dataBridge);
}
