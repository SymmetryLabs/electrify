#include "EngineUi.h"

#include <blueprint.h>

EngineUi::EngineUi(BlueprintProject& project_)
: project(project_)
{
    auto& blueprint = project.getBlueprint();
    nodeGrid = make_unique<NodeGrid>(blueprint);
}
