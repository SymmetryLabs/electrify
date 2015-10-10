#include "project.h"

#include "model.h"

Project::Project() = default;

Project::Project(unique_ptr<Model>&& model_)
: model(move(model_))
{
}

Project::~Project() = default;

Model& Project::getModel() const
{
    return *model;
}

void Project::setModel(unique_ptr<Model>&& model_)
{
    model = move(model_);
}
