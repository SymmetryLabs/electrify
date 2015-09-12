#pragma once
#include "globals.h"

class Model;
class Renderable;
class DataBridge;

class Project {

public:
    Project(unique_ptr<Model>&& model);
    virtual ~Project();

    Model& getModel() const;

    template<typename Archive>
    void serialize(Archive& archive);

    virtual unique_ptr<Renderable> releaseRenderable(DataBridge& dataBridge) = 0;

private:
    unique_ptr<Model> model;

};

#include "project.hpp"
