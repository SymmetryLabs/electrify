#pragma once
#include "BlueprintUiGlobals.h"

#include <blueprint_project.h>

#include "NodeGrid.h"

class EngineUi {

public:
    explicit EngineUi(BlueprintProject& project);

    unique_ptr<NodeGrid> nodeGrid;

private:
    BlueprintProject& project;

};
