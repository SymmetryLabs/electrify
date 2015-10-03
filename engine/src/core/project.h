#pragma once
#include "globals.h"

class Model;
class Renderable;
class DataBridge;

class Project {

public:
    Project();
    Project(unique_ptr<Model>&& model);
    virtual ~Project();

    Model& getModel() const;

    virtual unique_ptr<Renderable> releaseRenderable(DataBridge& dataBridge) = 0;

private:
    unique_ptr<Model> model;

    template <typename Archive>
    friend void serialize(Archive& archive, Project& project);

};
