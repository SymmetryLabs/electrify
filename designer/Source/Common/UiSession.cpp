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
, output(make_shared<Output>())
, appProperties{new ApplicationProperties()}
{
    session.getEngine().registerOutput(output);
    
    PropertiesFile::Options options;
    options.applicationName     = "Symmetry Labs Designer";
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Preferences";

    appProperties->setStorageParameters(options);
}

UiSession::~UiSession()
{
    session.getEngine().unregisterOutput(output);
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

ObservableSharedPtr<NodeGrid>& UiSession::getNodeGrid()
{
    return nodeGrid;
}
