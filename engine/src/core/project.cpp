#include "project.h"

#include "model.h"

Project::Project(unique_ptr<Model>&& model_)
: model(move(model_))
{
}

Project::~Project() = default;

Model& Project::getModel() const
{
    return *model;
}
