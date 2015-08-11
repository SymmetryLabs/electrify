/*
  ==============================================================================

    NodeGridWireView.h
    Created: 10 Aug 2015 5:20:20pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDWIREVIEW_H_INCLUDED
#define NODEGRIDWIREVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "BlueprintUiGlobals.h"

#include "NodeGridWire.h"

//==============================================================================
/*
*/
class NodeGridWireView    : public Component, ComponentListener
{
public:
    NodeGridWireView(NodeGridWire& nodeGridWire, Component& emittingComponent, Component& emittingParentComponent, Component& receivingComponent, Component& receivingParentComponent);
    ~NodeGridWireView();

    void paint (Graphics&);
    void resized();
    
    void componentBroughtToFront(Component& component) override;
    void componentMovedOrResized(Component& component, bool wasMoved, bool wasResized) override;

private:
    
    NodeGridWire& nodeGridWire;
    
    Component& emittingComponent;
    Component& emittingParentComponent;
    Component& receivingComponent;
    Component& receivingParentComponent;
    
    Point<int> emittingPos;
    Point<int> receivingPos;
    
    void calculateSize();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridWireView)
};


#endif  // NODEGRIDWIREVIEW_H_INCLUDED
