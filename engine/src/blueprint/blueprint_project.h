#pragma once
#include "globals.h"

#include "project.h"

class Blueprint;
class Model;
class DataBridge;

class BlueprintProject : public Project {

public:
    explicit BlueprintProject(const shared_ptr<Blueprint>& blueprint, unique_ptr<Model>&& model);

    Blueprint& getBlueprint() const;

    template<typename Archive>
    void serialize(Archive& archive);

    unique_ptr<Renderable> releaseRenderable(DataBridge& dataBridge) override;

private:
    shared_ptr<Blueprint> blueprint;

};

#include "blueprint_project.hpp"
