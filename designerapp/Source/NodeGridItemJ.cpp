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
NodeGridItemJ::NodeGridItemJ(NodeGridItem& nodeGridItem_)
: nodeGridItem(nodeGridItem_)
, dragStarted(false)
{
    setSize(200, 100);
    setBroughtToFrontOnMouseClick(true);
//    setObjectName(QString::fromStdString(componentGridItem->component->uuid));
    
    observeWithStart(nodeGridItem.positionChanged, [this] (Token) {
        setTopLeftPosition(nodeGridItem.x.Value(), nodeGridItem.y.Value());
    });
    
    int i = 0;
    signalViews.reserve(nodeGridItem.node->inputs.size());
    for (string input : nodeGridItem.node->inputs) {
        signalViews.push_back(make_unique<SignalView>());
        SignalView* signalView = signalViews.back().get();
        addAndMakeVisible(signalView);
        signalView->setTopLeftPosition(10, 20 + 20 * i);
        i++;
    }
    
    i = 0;
    signalViews.reserve(nodeGridItem.node->outputs.size());
    for (string output : nodeGridItem.node->outputs) {
        signalViews.push_back(make_unique<SignalView>());
        SignalView* signalView = signalViews.back().get();
        addAndMakeVisible(signalView);
        signalView->setTopRightPosition(getRight() - 10, 20 + 20 * i);
        i++;
    }
    
    Observe(nodeGridItem.selected, [this] (bool) {
        repaint();
    });
}

void NodeGridItemJ::setPos(Point<int> pos)
{
    nodeGridItem.setPos(pos.x, pos.y);
}

//==============================================================================
#pragma mark - Component
//==============================================================================

//==============================================================================
void NodeGridItemJ::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    int borderThickness = 1;
    if (nodeGridItem.selected.Value()) {
        g.setColour (Colours::blue);
        borderThickness = 2;
    } else {
        g.setColour (Colours::grey);
    }
    g.drawRect (getLocalBounds(), borderThickness);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText (nodeGridItem.node->name.Value(), getLocalBounds(),
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
    nodeGridItem.setSelected(true);
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
