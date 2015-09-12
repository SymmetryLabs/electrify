/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DesignerWindowComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DesignerWindowComponent::DesignerWindowComponent (Project& project, EngineUi& engineUi, Output& output)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (component = new OutputSimulationView (project, engineUi, output));
    component->setName ("new component");

    addAndMakeVisible (component2 = new NodeListView());
    component2->setName ("new component");

    addAndMakeVisible (component3 = new NodeGridView (*engineUi.nodeGrid));
    component3->setName ("new component");

    addAndMakeVisible (component4 = new PropertiesPanel());
    component4->setName ("new component");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1400, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

DesignerWindowComponent::~DesignerWindowComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    component = nullptr;
    component2 = nullptr;
    component3 = nullptr;
    component4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DesignerWindowComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DesignerWindowComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    component->setBounds (0, 0, 200, 200);
    component2->setBounds (0, 0 + 200, roundFloatToInt (200 * 1.0000f), getHeight() - 200);
    component3->setBounds (0 + 200, 0, getWidth() - 400, proportionOfHeight (1.0000f));
    component4->setBounds ((0 + 200) + (getWidth() - 400), 0, 200, proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DesignerWindowComponent"
                 componentName="" parentClasses="public Component" constructorParams="Project&amp; project, EngineUi&amp; engineUi, Output&amp; output"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="1400" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="new component" id="46591e2475c6760e" memberName="component"
                    virtualName="OutputSimulationView" explicitFocusOrder="0" pos="0 0 200 200"
                    class="Component" params="project, engineUi, output"/>
  <GENERICCOMPONENT name="new component" id="6a329d8e126ce007" memberName="component2"
                    virtualName="NodeListView" explicitFocusOrder="0" pos="0 0R 100% 200M"
                    posRelativeY="46591e2475c6760e" posRelativeW="46591e2475c6760e"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="new component" id="84be50bd51afc9b6" memberName="component3"
                    virtualName="NodeGridView" explicitFocusOrder="0" pos="0R 0 400M 100%"
                    posRelativeX="46591e2475c6760e" class="Component" params="*engineUi.nodeGrid"/>
  <GENERICCOMPONENT name="new component" id="36c4f7644b9e5f0f" memberName="component4"
                    virtualName="PropertiesPanel" explicitFocusOrder="0" pos="0R 0 200 100%"
                    posRelativeX="84be50bd51afc9b6" class="Component" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
