/*
  ==============================================================================

    ProjectDocument.cpp
    Created: 12 Oct 2015 5:40:11pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "ProjectDocument.h"

#include <project_file.h>

#include <blueprint.h>
#include <loader.h>
#include <compound_node.h>
#include <color.h>
#include <constant_color_node.h>
#include <incrementer.h>
#include <hsv_node.h>
#include <saw_wave.h>
#include <time_node.h>
#include <scale_transform.h>
#include <constant_node.h>
#include <perlin_noise_node.h>
#include <blueprint_project.h>

#include "UiSession.h"

ProjectDocument::ProjectDocument(UiSession& session_)
: FileBasedDocument(".symproj", "*.symproj",
    "Browse for Symmetry Engine project to load",
    "Choose file to save project to")
, session(session_)
{
}

void ProjectDocument::loadNew()
{
    session.setProject(createNewProject());
}

void ProjectDocument::loadDemoDocument()
{
    session.setProject(createDemoProject());
    changed();
}

String ProjectDocument::getDocumentTitle()
{
    if (!getFile().exists()) {
        return "Unnamed";
    }

    return getFile().getFileNameWithoutExtension();
}

Result ProjectDocument::loadDocument(const File& file)
{
    ProjectFile pf(file.getFullPathName().toStdString());
    if (auto project = pf.loadFromFile()) {
        project->setModel(createModel());

        session.setProject(move(project));

        return Result::ok();
    }
    return Result::fail("Could not load file");
}

Result ProjectDocument::saveDocument(const File& file)
{
    ProjectFile pf(file.getFullPathName().toStdString());
    if (pf.saveToFile(session.getProject())) {
        return Result::ok();
    }
    return Result::fail("Could not save file");

}

File ProjectDocument::getLastDocumentOpened()
{
    RecentlyOpenedFilesList recentFiles;
    recentFiles.restoreFromString(session.getAppProperties().getUserSettings()->getValue("recentFilterGraphFiles"));

    return recentFiles.getFile(0);
}

void ProjectDocument::setLastDocumentOpened(const File& file)
{
    RecentlyOpenedFilesList recentFiles;
    recentFiles.restoreFromString(session.getAppProperties().getUserSettings()->getValue("recentFilterGraphFiles"));

    recentFiles.addFile(file);

    session.getAppProperties().getUserSettings()->setValue("recentFilterGraphFiles", recentFiles.toString());
}

unique_ptr<Model> ProjectDocument::createModel() const
{
    Loader loader = Loader();
    return loader.loadJSON("../../../../../data/cubesExport2.json");
}

unique_ptr<BlueprintProject> ProjectDocument::createNewProject() const
{
    return make_unique<BlueprintProject>(makeBlueprint(), createModel());
}

unique_ptr<BlueprintProject> ProjectDocument::createDemoProject() const
{
    auto blueprint = makeBlueprint();

    auto compound = blueprint->makeSubnode<CompoundNode>("CompoundNode");
    compound->registerWirableOutput<Color>("color");

    auto constantColor = compound->makeSubnode<ConstantColorNode>("ConstantColorNode");
    auto incrementer = compound->makeSubnode<Incrementer>("Incrementer");

    compound->wireSubnodes(*constantColor->getOutput("output"), *incrementer->getInput("color"));
    compound->wireSubnodes(*incrementer->getOutput("output"), *compound->getWirableOutput("color"));

    auto hsvNode = blueprint->makeSubnode<HsvNode>("HsvNode");
    auto sawWaveNode = blueprint->makeSubnode<SawWave>("SawWave");
    auto timeNode = blueprint->makeSubnode<TimeNode>("TimeNode");
    auto scaleTransform = blueprint->makeSubnode<ScaleTransform>("ScaleTransform");
    auto multiplyAmountNode = blueprint->makeSubnode<ConstantFloatNode>("ConstantFloatNode");
    auto perlinNoiseNode = blueprint->makeSubnode<PerlinNoiseNode>("PerlinNoiseNode");
    auto frequency = blueprint->makeSubnode<ConstantFloatNode>("ConstantFloatNode");

    blueprint->wireSubnodes(*frequency->getOutput("output"), *sawWaveNode->getInput("frequency"));
    blueprint->wireSubnodes(*multiplyAmountNode->getOutput("output"), *scaleTransform->getInput("multiplier"));
    blueprint->wireSubnodes(*timeNode->getOutput("output"), *scaleTransform->getInput("input"));
    blueprint->wireSubnodes(*scaleTransform->getOutput("output"), *perlinNoiseNode->getInput("zInput"));
    blueprint->wireSubnodes(*perlinNoiseNode->getOutput("output"), *hsvNode->getInput("hue"));

    blueprint->wireSubnodes(*hsvNode->getOutput("output"), *blueprint->getWirableOutput("color"));

    return make_unique<BlueprintProject>(blueprint, createModel());
}
