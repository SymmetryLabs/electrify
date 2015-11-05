#include "session.h"

#include "project.h"
#include "engine.h"
#include "model.h"

Session::Session(Engine& engine_)
: engine(engine_)
{
}

bool Session::hasProject() const
{
    return project.get();
}

const unique_ptr<Project>& Session::getProject() const
{
    return project;
}

void Session::setProject(unique_ptr<Project>&& project_)
{
    project = move(project_);
    engine.notifyProjectChanged(*project);
}

Model& Session::getModel() const
{
    return project->getModel();
}

Engine& Session::getEngine() const
{
    return engine;
}
