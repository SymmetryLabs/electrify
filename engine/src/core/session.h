#pragma once
#include "globals.h"

class Project;
class Engine;
class Model;

class Session {

public:
    explicit Session(Engine& engine);

    bool hasProject() const;
    const unique_ptr<Project>& getProject() const;
    void setProject(unique_ptr<Project>&& project);

    Model& getModel() const;
    Engine& getEngine() const;

private:
    Engine& engine;

    unique_ptr<Project> project;

};
