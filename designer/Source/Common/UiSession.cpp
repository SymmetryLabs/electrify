#include "UiSession.h"

#include <session.h>
#include <blueprint_project.h>
#include <blueprint.h>
#include <model.h>
#include <output.h>
#include <engine.h>

#include "NodeGrid.h"

UiSession::UiSession(Session& session_)
: session(session_)
, appProperties{new ApplicationProperties()}
{
    PropertiesFile::Options options;
    options.applicationName     = "Symmetry Labs Designer";
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Preferences";

    appProperties->setStorageParameters(options);
}

ApplicationProperties& UiSession::getAppProperties()
{
    return *appProperties;
}

const unique_ptr<Project>& UiSession::getProject() const
{
    return session.getProject();
}

void UiSession::setProject(unique_ptr<Project>&& project)
{
    setOutput(make_shared<Output>(project->getModel().pixels.size()));
    session.setProject(forward<unique_ptr<Project>>(project));
    nodeGrid = make_unique<NodeGrid>(getBlueprint());
}

BlueprintProject& UiSession::getBlueprintProject() const
{
    auto& project = *session.getProject();
    return dynamic_cast<BlueprintProject&>(project);
}

Blueprint& UiSession::getBlueprint() const
{
    return getBlueprintProject().getBlueprint();
}

Model& UiSession::getModel() const
{
    return session.getModel();
}

Output& UiSession::getOutput() const
{
    return *output;
}

NodeGrid& UiSession::getNodeGrid() const
{
    return *nodeGrid;
}

void UiSession::setOutput(const shared_ptr<Output>& output_)
{
    if (output) {
        session.getEngine().unregisterOutput(output);
    }
    output = output_;
    if (output) {
        session.getEngine().registerOutput(output);
    }
}
