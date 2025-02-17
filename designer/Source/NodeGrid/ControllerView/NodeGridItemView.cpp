/*
  ==============================================================================

    NodeGridItemView.cpp
    Created: 3 Aug 2015 5:05:56pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridItemView.h"

//==============================================================================
NodeGridItemView::NodeGridItemView(NodeGridItem& nodeGridItem_, NodeGrid& nodeGrid)
: nodeGridItem(nodeGridItem_)
, nodeGrid(nodeGrid)
, dragStarted(false)
{
    setSize(200, 100);
    setBroughtToFrontOnMouseClick(true);
    setName(nodeGridItem.getName());
    
    int i = 0;
    signalViews.reserve(nodeGridItem.inputs.size());
    for (const auto& input : nodeGridItem.inputs) {
        signalViews.push_back(make_unique<SignalView>(*input.get(), nodeGrid));
        SignalView* signalView = signalViews.back().get();
        signalView->setTopLeftPosition(10, 20 + 20 * i);
        addAndMakeVisible(signalView);
        i++;
    }
    
    i = 0;
    signalViews.reserve(nodeGridItem.outputs.size());
    for (const auto& output : nodeGridItem.outputs) {
        signalViews.push_back(make_unique<SignalView>(*output.get(), nodeGrid));
        SignalView* signalView = signalViews.back().get();
        signalView->setTopRightPosition(getRight() - 10, 20 + 20 * i);
        addAndMakeVisible(signalView);
        i++;
    }
    
    scopedObserve(nodeGridItem.x.merge(nodeGridItem.y).tokenize(), [this] (void*) {
        setTopLeftPosition(nodeGridItem.x.getValue(), nodeGridItem.y.getValue());
    });
    
    scopedObserve(nodeGridItem.selected, [this] (bool) {
        repaint();
    });
}

void NodeGridItemView::setPos(Point<int> pos)
{
    nodeGridItem.setPos(pos.x, pos.y);
}

SignalView* NodeGridItemView::signalViewFromSignal(const NodeGridSocket& gridSocket) const
{
    for (auto& signalView : signalViews) {
        if (&signalView->socket.nodeSignal == &gridSocket.nodeSignal) {
            return signalView.get();
        }
    }
    return nullptr;
}

//==============================================================================
#pragma mark - Component
//==============================================================================

//==============================================================================
void NodeGridItemView::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    int borderThickness = 1;
    if (nodeGridItem.selected.getValue()) {
        g.setColour (Colours::blue);
        borderThickness = 2;
    } else {
        g.setColour (Colours::grey);
    }
    g.drawRect (getLocalBounds(), borderThickness);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText (nodeGridItem.getName(), getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void NodeGridItemView::resized()
{
}

//==============================================================================
void NodeGridItemView::mouseDown(const MouseEvent& e)
{
    dragStarted = true;
    dragger.startDraggingComponent(this, e);
    nodeGridItem.setSelected(true);
}

void NodeGridItemView::mouseDrag(const MouseEvent& e)
{
    if (dragStarted)
        dragger.dragComponent(this, e, nullptr);
}

void NodeGridItemView::mouseUp(const MouseEvent& e)
{
    dragStarted = false;
    setPos(getPosition());
}
