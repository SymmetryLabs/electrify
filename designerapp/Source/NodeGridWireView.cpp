/*
  ==============================================================================

    NodeGridWireView.cpp
    Created: 10 Aug 2015 5:20:20pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NodeGridWireView.h"

//==============================================================================
NodeGridWireView::NodeGridWireView(NodeGridWire& nodeGridWire, Component& emittingComponent, Component& emittingParentComponent, Component& receivingComponent, Component& receivingParentComponent)
: nodeGridWire(nodeGridWire)
, emittingComponent(emittingComponent)
, emittingParentComponent(emittingParentComponent)
, receivingComponent(receivingComponent)
, receivingParentComponent(receivingParentComponent)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setOpaque(false);
    setInterceptsMouseClicks(false, false);
    
    emittingParentComponent.addComponentListener(this);
    receivingParentComponent.addComponentListener(this);
    
    calculateSize();
}

NodeGridWireView::~NodeGridWireView()
{
    emittingParentComponent.removeComponentListener(this);
    receivingParentComponent.removeComponentListener(this);
}

void NodeGridWireView::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

//    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    Point<int> emittingLocalPoint = getLocalPoint(getParentComponent(), emittingPos);
    Point<int> receivingLocalPoint = getLocalPoint(getParentComponent(), receivingPos);
    g.drawArrow(Line<int>(emittingLocalPoint, receivingLocalPoint).toFloat(), 2, 10, 10);

//    g.setColour (Colours::lightblue);
//    g.setFont (14.0f);
//    g.drawText ("NodeGridWireView", getLocalBounds(),
//                Justification::centred, true);   // draw some placeholder text
}

void NodeGridWireView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void NodeGridWireView::componentBroughtToFront(Component& component)
{
    toFront(false);
}


void NodeGridWireView::componentMovedOrResized(Component& component, bool wasMoved, bool wasResized)
{
    calculateSize();
}

void NodeGridWireView::calculateSize()
{
    Point<int> emittingLocalPos = emittingComponent.getBounds().getCentre();
    Point<int> receivingLocalPos = receivingComponent.getBounds().getCentre();
    
    emittingPos = getParentComponent()->getLocalPoint(emittingComponent.getParentComponent(), emittingLocalPos);
    receivingPos = getParentComponent()->getLocalPoint(receivingComponent.getParentComponent(), receivingLocalPos);
    
    int left = min(emittingPos.x, receivingPos.x) - 10;
    int right = max(emittingPos.x, receivingPos.x) + 10;
    int top = min(emittingPos.y, receivingPos.y) - 10;
    int bottom = max(emittingPos.y, receivingPos.y) + 10;
    
    setBounds(Rectangle<int>::leftTopRightBottom(left, top, right, bottom));
}
