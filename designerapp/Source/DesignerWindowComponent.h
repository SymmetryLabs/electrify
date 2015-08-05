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

#ifndef __JUCE_HEADER_8C0E92855EE0ECC0__
#define __JUCE_HEADER_8C0E92855EE0ECC0__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "OutputSimulationJ.h"
#include "NodeListJ.h"
#include "NodeGridJ.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DesignerWindowComponent  : public Component
{
public:
    //==============================================================================
    DesignerWindowComponent (Engine* engine, EngineUi* engineUi, Output* output);
    ~DesignerWindowComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    EngineUi* engineUi;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<OutputSimulationJ> component;
    ScopedPointer<NodeListJ> component2;
    ScopedPointer<NodeGridJ> component3;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DesignerWindowComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8C0E92855EE0ECC0__
