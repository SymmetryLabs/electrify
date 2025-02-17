/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.0.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_23AD31501534E282__
#define __JUCE_HEADER_23AD31501534E282__

//[Headers]     -- You can add your own extra header files here --
#include "BlueprintUiGlobals.h"

#include "NodeGridSocket.h"
#include "NodeGridItem.h"
#include "NodeGrid.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SignalView  : public Component
{
public:
    //==============================================================================
    SignalView (NodeGridSocket& socket, NodeGrid& nodeGrid);
    ~SignalView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    NodeGridSocket& socket;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseEnter (const MouseEvent& e);
    void mouseExit (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    NodeGrid& nodeGrid;

    bool dragStarted = false;
    SignalView* lastHover;
    bool hovering = false;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SignalView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_23AD31501534E282__
