/*
  ==============================================================================

    NodeGridWireView.cpp
    Created: 10 Aug 2015 5:20:20pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridWireView.h"

//==============================================================================
NodeGridWireView::NodeGridWireView(NodeGridWire& nodeGridWire, Component* emittingComponent, Component* emittingParentComponent, Component* receivingComponent, Component* receivingParentComponent)
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
    
    if (emittingParentComponent) {
        emittingParentComponent->addComponentListener(this);
    }
    if (receivingParentComponent && emittingParentComponent != receivingParentComponent) {
        receivingParentComponent->addComponentListener(this);
    }
    
    observe(nodeGridWire.emittingPos.merge(nodeGridWire.receivingPos), [this] (Point<int>) {
        calculateBounds();
    });
}

NodeGridWireView::~NodeGridWireView()
{
    if (emittingParentComponent) {
        emittingParentComponent->removeComponentListener(this);
    }
    if (receivingParentComponent && emittingParentComponent != receivingParentComponent) {
        receivingParentComponent->removeComponentListener(this);
    }
}

void NodeGridWireView::parentHierarchyChanged()
{
    if (getParentComponent()) {
        calculatePositions();
        
        if (emittingComponent && !receivingComponent) {
            nodeGridWire.receivingPos << nodeGridWire.emittingPos.getValue();
        } else if (receivingComponent && !emittingComponent) {
            nodeGridWire.emittingPos << nodeGridWire.receivingPos.getValue();
        }
    }
}

void NodeGridWireView::paint (Graphics& g)
{
    g.setColour (Colours::grey);
    
    Point<int> emittingLocalPoint = getLocalPoint(getParentComponent(), nodeGridWire.emittingPos.getValue());
    Point<int> receivingLocalPoint = getLocalPoint(getParentComponent(), nodeGridWire.receivingPos.getValue());
    g.drawArrow(Line<int>(emittingLocalPoint, receivingLocalPoint).toFloat(), 2, 10, 10);
}

void NodeGridWireView::resized()
{
}

void NodeGridWireView::componentBroughtToFront(Component& component)
{
    toFront(false);
}

void NodeGridWireView::componentMovedOrResized(Component& component, bool wasMoved, bool wasResized)
{
    calculatePositions();
}

void NodeGridWireView::calculatePositions()
{
    if (emittingComponent) {
        Point<int> emittingLocalPos = emittingComponent->getBounds().getCentre();
        nodeGridWire.emittingPos << getParentComponent()->getLocalPoint(emittingComponent->getParentComponent(), emittingLocalPos);
    }
    if (receivingComponent) {
        Point<int> receivingLocalPos = receivingComponent->getBounds().getCentre();
        nodeGridWire.receivingPos << getParentComponent()->getLocalPoint(receivingComponent->getParentComponent(), receivingLocalPos);
    }
}

void NodeGridWireView::calculateBounds()
{
    int left = min(nodeGridWire.emittingPos.getValue().x, nodeGridWire.receivingPos.getValue().x) - 10;
    int right = max(nodeGridWire.emittingPos.getValue().x, nodeGridWire.receivingPos.getValue().x) + 10;
    int top = min(nodeGridWire.emittingPos.getValue().y, nodeGridWire.receivingPos.getValue().y) - 10;
    int bottom = max(nodeGridWire.emittingPos.getValue().y, nodeGridWire.receivingPos.getValue().y) + 10;
    
    setBounds(Rectangle<int>::leftTopRightBottom(left, top, right, bottom));
}
