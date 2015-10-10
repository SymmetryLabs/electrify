/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "DesignerWindowComponent.h"

#include <engine.h>
#include <output.h>

#include <color.h>
#include <constant_color_node.h>
#include <color_doubler.h>
#include <signal.h>
#include <pixel.h>
#include <group.h>
#include <frame_context.h>
#include <square_wave.h>
#include <incrementer.h>
#include <engine.h>
#include <loader.h>
#include <compound_node.h>
#include <blueprint.h>
#include <hsv_node.h>
#include <saw_wave.h>
#include <constant_node.h>
#include <perlin_noise_node.h>
#include <time_node.h>
#include <scale_transform.h>
#include <blueprint_project.h>
#include <data_relay.h>
#include <project_file.h>
#include <file_utils.h>

#include "EngineUi.h"

//==============================================================================
class DesignerApplication  : public JUCEApplication
{
public:
    //==============================================================================
    DesignerApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        
        engine = make_unique<Engine>();
        dataRelay = &engine->getDataRelay();
        
        /* file loading */
        Loader loader = Loader();
        auto model = loader.loadJSON("../../../../../data/cubesExport2.json");
        auto& modelRef = *model;
        cout << "file loaded" << endl;
        
        unique_ptr<Project> project;
        
        if (file_exists("default.symproj")) {
            ProjectFile pf("default.symproj");
            project = pf.loadFromFile();
            project->setModel(move(model));
        } else {
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
            
            project = make_unique<BlueprintProject>(blueprint, move(model));
            
            ProjectFile pf("default.symproj");
            pf.saveToFile(project);
        }
        
        unique_ptr<BlueprintProject> blueprintProject = unique_ptr<BlueprintProject>(dynamic_cast<BlueprintProject*>(project.release()));
        auto& projectRef = *blueprintProject;
        
        engine->loadProject(move(blueprintProject));
        
        output = make_unique<Output>(modelRef.pixels.size());
        engine->registerOutput(*output);
        
        engineUi = make_unique<EngineUi>(projectRef);
        
        // engine->setProfilerEnabled(true);
        engine->start();
        
        designerWindow = new DesignerWindow (getApplicationName(), projectRef, *engineUi, *output);
    }

    void shutdown() override
    {
        engine->wait();
        designerWindow = nullptr; // (deletes our window)
        dataRelay = nullptr;
        engineUi = nullptr;
        engine->unregisterOutput(*output);
        output = nullptr;
        engine = nullptr;
    }
    
    //==============================================================================
    void preMainRunLoop() override
    {
        if (dataRelay) {
            dataRelay->processIncomingTransactions();
        }
    }
    
    void postMainRunLoop() override
    {
        if (dataRelay) {
            dataRelay->commitOutgoingTransaction();
        }
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        if (engine) {
            engine->stop();
        }
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentNode class.
    */
    class DesignerWindow    : public DocumentWindow
    {
    public:
        DesignerWindow (String name,
                        Project& project,
                        EngineUi& engineUi,
                        Output& output)
            : DocumentWindow (name,
                              Colours::lightgrey,
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new DesignerWindowComponent(project, engineUi, output), true);
            setResizable (true, true);

            centreWithSize (getWidth(), getHeight());
            setBounds(getBounds().withY(0));
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content node instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DesignerWindow)
    };

private:
    ScopedPointer<DesignerWindow> designerWindow;
    
    unique_ptr<Engine> engine;
    unique_ptr<EngineUi> engineUi;
    unique_ptr<Output> output;
    DataRelay* dataRelay = nullptr;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (DesignerApplication)
