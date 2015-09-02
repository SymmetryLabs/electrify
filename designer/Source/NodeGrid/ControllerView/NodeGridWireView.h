/*
  ==============================================================================

    NodeGridWireView.h
    Created: 10 Aug 2015 5:20:20pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDWIREVIEW_H_INCLUDED
#define NODEGRIDWIREVIEW_H_INCLUDED

#include "BlueprintUiGlobals.h"

#include <observes.h>

#include "NodeGridWire.h"

//==============================================================================
/*
*/
class NodeGridWireView : public Component, ComponentListener, Observes
{
    
public:
    NodeGridWireView(NodeGridWire& nodeGridWire, Component* emittingComponent, Component* emittingParentComponent, Component* receivingComponent, Component* receivingParentComponent);
    ~NodeGridWireView();

    void parentHierarchyChanged() override;
    void paint(Graphics&) override;
    void resized() override;
    
    bool hitTest(int x, int y) override;
    void mouseDown(const MouseEvent& e) override;
    
    void componentBroughtToFront(Component& component) override;
    void componentMovedOrResized(Component& component, bool wasMoved, bool wasResized) override;

private:
    
    NodeGridWire& nodeGridWire;
    
    Component* emittingComponent;
    Component* emittingParentComponent;
    Component* receivingComponent;
    Component* receivingParentComponent;
    
    void calculatePositions();
    void calculateBounds();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridWireView)
};


#endif  // NODEGRIDWIREVIEW_H_INCLUDED
