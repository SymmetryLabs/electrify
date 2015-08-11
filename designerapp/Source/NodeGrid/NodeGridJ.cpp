/*
  ==============================================================================

    NodeGridJ.cpp
    Created: 3 Aug 2015 5:05:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NodeGridJ.h"

#include "NodeListJ.h"

//==============================================================================
NodeGridJ::NodeGridJ(NodeGrid* nodeGrid_)
{
    Observe(nodeGrid, [this] (NodeGrid* nodeGrid) {
        removeAllGridItems();
        removeAllGridWireViews();
        if (nodeGrid != nullptr) {
            for (const shared_ptr<NodeGridItem>& gridItem : nodeGrid->gridItems) {
                addWithGridItem(gridItem.get());
            }
            for (const shared_ptr<NodeGridWire>& gridWire : nodeGrid->gridWires) {
                addViewWithGridWire(gridWire.get());
            }
        }
    });
    
    this->nodeGrid <<= nodeGrid_;
    
    observeWithCapture(REACTIVE_PTR(nodeGrid, gridItems.valueAdded), [this] (const pair<size_t, reference_wrapper<shared_ptr<NodeGridItem>>>& p) {
        addWithGridItem(p.second.get().get());
    });
    
    observeWithCapture(REACTIVE_PTR(nodeGrid, gridItems.valueRemoved), [this] (const pair<size_t, shared_ptr<NodeGridItem>>& p) {
        removeWithGridItem(p.second.get());
    });
    
    observeWithCapture(REACTIVE_PTR(nodeGrid, gridWires.valueAdded), [this] (const pair<size_t, reference_wrapper<shared_ptr<NodeGridWire>>>& p) {
        addViewWithGridWire(p.second.get().get());
    });
    
    observeWithCapture(REACTIVE_PTR(nodeGrid, gridWires.valueRemoved), [this] (const pair<size_t, shared_ptr<NodeGridWire>>& p) {
        removeViewWithGridWire(p.second.get());
    });
}

void NodeGridJ::addWithGridItem(NodeGridItem* gridItem)
{
    gridItems.push_back(make_unique<NodeGridItemJ>(*gridItem));
    addAndMakeVisible(gridItems.back().get());
}

void NodeGridJ::removeWithGridItem(NodeGridItem* gridItem)
{
}

void NodeGridJ::removeAllGridItems()
{
}


NodeGridItemJ* NodeGridJ::gridItemViewWithGridItem(NodeGridItem& gridItem)
{
    for (auto& gridItemView : gridItems) {
        if (&gridItemView->nodeGridItem == &gridItem) {
            return gridItemView.get();
        }
    }
    return nullptr;
}

void NodeGridJ::addViewWithGridWire(NodeGridWire* gridWire)
{
    NodeGridItemJ* emittingGridItem = gridItemViewWithGridItem(gridWire->emittingGridItem);
    NodeGridItemJ* receivingGridItem = gridItemViewWithGridItem(gridWire->receivingGridItem);
    SignalView* emittingSignalView = emittingGridItem->signalViewFromSignal(gridWire->nodeWire.emittingOutputName);
    SignalView* receivingSignalView = receivingGridItem->signalViewFromSignal(gridWire->nodeWire.receivingInputName);
    gridWireViews.push_back(make_unique<NodeGridWireView>(*gridWire, *emittingSignalView, *emittingGridItem, *receivingSignalView, *receivingGridItem));
    addAndMakeVisible(gridWireViews.back().get());
}

void NodeGridJ::removeViewWithGridWire(NodeGridWire* gridWire)
{
}

void NodeGridJ::removeAllGridWireViews()
{
}

#pragma mark - Component

void NodeGridJ::paint (Graphics& g)
{
}

void NodeGridJ::resized()
{
}

void NodeGridJ::mouseDrag(const MouseEvent& event)
{
    
}

#pragma mark - DragAndDropTarget

bool NodeGridJ::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
    if (dragSourceDetails.sourceComponent) {
        Component* sourceComponent = dragSourceDetails.sourceComponent;
        if (dynamic_cast<NodeListJ*>(sourceComponent->getParentComponent())) {
            return true;
        }
    }
    return false;
}

void NodeGridJ::itemDropped (const SourceDetails& dragSourceDetails)
{
    if (dragSourceDetails.sourceComponent) {
        Component* sourceComponent = dragSourceDetails.sourceComponent;
        if (dynamic_cast<NodeListJ*>(sourceComponent->getParentComponent())) {
            const var& description = dragSourceDetails.description;
            int i = 0;
            while (i < description.size()) {
                string name = description[i++].toString().toStdString();
                cout << "Added " << name << endl;
                nodeGrid.Value()->addNode(name, dragSourceDetails.localPosition.x, dragSourceDetails.localPosition.y);
            }
        }
    }
}
