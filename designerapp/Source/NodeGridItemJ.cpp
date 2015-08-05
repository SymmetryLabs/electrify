/*
  ==============================================================================

    NodeGridItemJ.cpp
    Created: 3 Aug 2015 5:05:56pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NodeGridItemJ.h"

//==============================================================================
NodeGridItemJ::NodeGridItemJ(NodeGridItem* nodeGridItem_)
: nodeGridItem(nodeGridItem_)
, dragStarted(false)
{
    setSize(200, 100);
//    setObjectName(QString::fromStdString(componentGridItem->component->uuid));
    
    Observe(nodeGridItem->positionChanged, [this] (Token) {
        setTopLeftPosition(nodeGridItem->x.Value(), nodeGridItem->y.Value());
    });
    setTopLeftPosition(nodeGridItem->x.Value(), nodeGridItem->y.Value());
}

void NodeGridItemJ::setPos(Point<int> pos)
{
    nodeGridItem->setPos(pos.x, pos.y);
}

//==============================================================================
#pragma mark - Component
//==============================================================================

//==============================================================================
void NodeGridItemJ::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText (nodeGridItem->node->name.Value(), getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void NodeGridItemJ::resized()
{
}

//==============================================================================
void NodeGridItemJ::mouseDown(const MouseEvent& e)
{
    dragStarted = true;
    dragger.startDraggingComponent(this, e);
}

void NodeGridItemJ::mouseDrag(const MouseEvent& e)
{
    if (dragStarted)
        dragger.dragComponent(this, e, nullptr);
}

void NodeGridItemJ::mouseUp(const MouseEvent& e)
{
    dragStarted = false;
    setPos(getPosition());
}
