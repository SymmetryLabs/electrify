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
#include "NodeGridView.h"
//[/Headers]

#include "SignalView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SignalView::SignalView (string signalName, NodeGrid& nodeGrid, NodeGridItem& nodeGridItem)
    : signalName(signalName),
      nodeGrid(nodeGrid),
      nodeGridItem(nodeGridItem)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (10, 10);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SignalView::~SignalView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SignalView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    if (hovering) {
        g.setColour (Colours::darkslateblue);
    } else {
        g.setColour (Colours::darkmagenta);
    }
    g.fillEllipse (0.0f, 0.0f, 10.0f, 10.0f);
    //[/UserPaint]
}

void SignalView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SignalView::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
    hovering = true;
    repaint();
    //[/UserCode_mouseEnter]
}

void SignalView::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
    hovering = false;
    repaint();
    //[/UserCode_mouseExit]
}

void SignalView::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    dragStarted = true;
    nodeGrid.draggingWireStarted(nodeGridItem, signalName);
    lastHover = this;
    hovering = true;
    //[/UserCode_mouseDown]
}

void SignalView::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    if (dragStarted) {
        NodeGridView* nodeGridView = findParentComponentOfClass<NodeGridView>();
        Point<int> p = nodeGridView->getLocalPoint(this, e.getPosition());
        nodeGrid.draggingWireMoved(p);
        
        Component* component = nodeGridView->getComponentAt(p);
        SignalView* signalView = dynamic_cast<SignalView*>(component);
        if (lastHover && signalView != lastHover) {
            lastHover->hovering = false;
            lastHover = signalView;
        }
        if (signalView) {
            lastHover = signalView;
            signalView->hovering = true;
            signalView->repaint();
        }
    }
    //[/UserCode_mouseDrag]
}

void SignalView::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    if (dragStarted) {
        dragStarted = false;
        if (lastHover) {
            lastHover->hovering = false;
            lastHover = nullptr;
        }
        
        NodeGridView* nodeGridView = findParentComponentOfClass<NodeGridView>();
        Point<int> p = nodeGridView->getLocalPoint(this, e.getPosition());
        
        Component* component = nodeGridView->getComponentAt(p);
        SignalView* signalView = dynamic_cast<SignalView*>(component);
        if (signalView) {
            nodeGrid.draggingWireEnded(signalView->nodeGridItem, signalView->signalName);
        }
    }
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SignalView" componentName=""
                 parentClasses="public Component" constructorParams="string signalName, NodeGrid&amp; nodeGrid, NodeGridItem&amp; nodeGridItem"
                 variableInitialisers="signalName(signalName),&#10;nodeGrid(nodeGrid),&#10;nodeGridItem(nodeGridItem)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="10" initialHeight="10">
  <METHODS>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff">
    <ELLIPSE pos="0 0 10 10" fill="solid: ffff0000" hasStroke="0"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
