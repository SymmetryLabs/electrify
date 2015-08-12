/*
  ==============================================================================

    NodeGridView.cpp
    Created: 3 Aug 2015 5:05:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridView.h"

#include "NodeListView.h"

//==============================================================================
NodeGridView::NodeGridView(NodeGrid* nodeGrid_)
{
    Observe(nodeGrid, [this] (NodeGrid* nodeGrid) {
        removeAllGridItems();
        removeAllGridWireViews();
        if (nodeGrid != nullptr) {
            for (const auto& gridItem : nodeGrid->gridItems) {
                addWithGridItem(gridItem.get());
            }
            for (const auto& gridWire : nodeGrid->gridWires) {
                addViewWithGridWire(gridWire.get());
            }
            resetZOrdering();
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
    
    observeWithCapture(REACTIVE_PTR(nodeGrid, draggingWire), [this] (const shared_ptr<NodeGridWire>& draggingWire) {
        if (draggingWire) {
            NodeGridItemView* emittingGridItem = nullptr;
            NodeGridItemView* receivingGridItem = nullptr;
            SignalView* emittingSignalView = nullptr;
            SignalView* receivingSignalView = nullptr;
            if (draggingWire->emittingGridItem) {
                emittingGridItem = gridItemViewWithGridItem(*draggingWire->emittingGridItem);
                emittingSignalView = emittingGridItem->signalViewFromSignal(draggingWire->emittingOutputName);
            }
            if (draggingWire->receivingGridItem) {
                receivingGridItem = gridItemViewWithGridItem(*draggingWire->receivingGridItem);
                receivingSignalView = receivingGridItem->signalViewFromSignal(draggingWire->receivingInputName);
            }
            draggingWireView = make_unique<NodeGridWireView>(*draggingWire, emittingSignalView, emittingGridItem, receivingSignalView, receivingGridItem);
            addAndMakeVisible(draggingWireView.get());
        } else if (draggingWireView) {
            removeChildComponent(draggingWireView.get());
            draggingWireView = nullptr;
        }
    });
}

void NodeGridView::addWithGridItem(NodeGridItem* gridItem)
{
    gridItems.push_back(make_unique<NodeGridItemView>(*gridItem, *nodeGrid.Value()));
    addAndMakeVisible(gridItems.back().get());
}

void NodeGridView::removeWithGridItem(NodeGridItem* gridItem)
{
}

void NodeGridView::removeAllGridItems()
{
}

NodeGridItemView* NodeGridView::gridItemViewWithGridItem(NodeGridItem& gridItem)
{
    for (auto& gridItemView : gridItems) {
        if (&gridItemView->nodeGridItem == &gridItem) {
            return gridItemView.get();
        }
    }
    return nullptr;
}

void NodeGridView::addViewWithGridWire(NodeGridWire* gridWire)
{
    NodeGridItemView* emittingGridItem = gridItemViewWithGridItem(*gridWire->emittingGridItem);
    NodeGridItemView* receivingGridItem = gridItemViewWithGridItem(*gridWire->receivingGridItem);
    SignalView* emittingSignalView = emittingGridItem->signalViewFromSignal(gridWire->emittingOutputName);
    SignalView* receivingSignalView = receivingGridItem->signalViewFromSignal(gridWire->receivingInputName);
    gridWireViews.push_back(make_unique<NodeGridWireView>(*gridWire, emittingSignalView, emittingGridItem, receivingSignalView, receivingGridItem));
    addAndMakeVisible(gridWireViews.back().get());
}

void NodeGridView::removeViewWithGridWire(NodeGridWire* gridWire)
{
}

void NodeGridView::removeAllGridWireViews()
{
}

void NodeGridView::resetZOrdering()
{
    for (int i = 0; i < getNumChildComponents(); i++) {
        auto component = getChildComponent(i++);
        component->toFront(false);
    }
}

#pragma mark - Component

void NodeGridView::paint (Graphics& g)
{
}

void NodeGridView::resized()
{
}

void NodeGridView::mouseDrag(const MouseEvent& event)
{
    
}

#pragma mark - DragAndDropTarget

bool NodeGridView::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
    if (dragSourceDetails.sourceComponent) {
        Component* sourceComponent = dragSourceDetails.sourceComponent;
        if (dynamic_cast<NodeListView*>(sourceComponent->getParentComponent())) {
            return true;
        }
    }
    return false;
}

void NodeGridView::itemDropped (const SourceDetails& dragSourceDetails)
{
    if (dragSourceDetails.sourceComponent) {
        Component* sourceComponent = dragSourceDetails.sourceComponent;
        if (dynamic_cast<NodeListView*>(sourceComponent->getParentComponent())) {
            const var& description = dragSourceDetails.description;
            for (int i = 0; i < description.size(); i++) {
                string name = description[i].toString().toStdString();
                cout << "Added " << name << endl;
                nodeGrid.Value()->addNode(name, dragSourceDetails.localPosition.x, dragSourceDetails.localPosition.y);
            }
        }
    }
}
