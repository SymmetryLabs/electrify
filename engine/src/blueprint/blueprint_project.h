#pragma once
#include "globals.h"

#include "project.h"

class Blueprint;
class Model;
class DataBridge;

class BlueprintProject : public Project {

public:
    BlueprintProject() = default;
    explicit BlueprintProject(const shared_ptr<Blueprint>& blueprint, unique_ptr<Model>&& model);

    Blueprint& getBlueprint() const;

    unique_ptr<Renderable> releaseRenderable(DataBridge& dataBridge) override;

private:
    shared_ptr<Blueprint> blueprint;

    template <typename Archive>
    friend void serialize(Archive& archive, BlueprintProject& project);

};
