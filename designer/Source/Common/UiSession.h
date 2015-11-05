#pragma once
#include "BlueprintUiGlobals.h"

class Session;
class Project;
class BlueprintProject;
class Blueprint;
class Model;
class Output;

class NodeGrid;

class UiSession {

public:
    explicit UiSession(Session& session);
    ~UiSession();
    
    ApplicationProperties& getAppProperties();

    const unique_ptr<Project>& getProject() const;
    void setProject(unique_ptr<Project>&& project);

    BlueprintProject& getBlueprintProject() const;
    Blueprint& getBlueprint() const;

    Model& getModel() const;
    Output& getOutput() const;

    ObservableSharedPtr<NodeGrid>& getNodeGrid();

private:
    Session& session;

    shared_ptr<Output> output;
    
    ScopedPointer<ApplicationProperties> appProperties;
    ObservableSharedPtr<NodeGrid> nodeGrid;

};
