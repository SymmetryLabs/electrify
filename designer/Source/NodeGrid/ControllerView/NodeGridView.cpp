/*
  ==============================================================================

    NodeGridView.cpp
    Created: 3 Aug 2015 5:05:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "NodeGridView.h"

#include "NodeListView.h"
#include "NodeGridItemNode.h"
#include "NodeGridItemSocket.h"

//==============================================================================
NodeGridView::NodeGridView(NodeGrid& nodeGrid_)
: nodeGrid(nodeGrid_)
{
    setWantsKeyboardFocus(true);
    
    nodeGrid.gridItems.makeSlave(gridItemViews, [this] (const shared_ptr<NodeGridItem>& gridItem) {
        auto gridItemView = make_shared<NodeGridItemView>(*gridItem, nodeGrid);
        addAndMakeVisible(gridItemView.get());
        return gridItemView;
    }, [this] (const shared_ptr<NodeGridItemView>& gridItem) {
        removeChildComponent(gridItem.get());
    });
    nodeGrid.gridOutputs.makeSlave(gridOutputViews, [this] (const shared_ptr<NodeGridItem>& gridItem) {
        auto gridItemView = make_shared<NodeGridItemView>(*gridItem, nodeGrid);
        addAndMakeVisible(gridItemView.get());
        return gridItemView;
    }, [this] (const shared_ptr<NodeGridItemView>& gridItem) {
        removeChildComponent(gridItem.get());
    });
    nodeGrid.gridWires.makeSlave(gridWireViews, [this] (const shared_ptr<NodeGridWire>& gridWire) {
        return makeGridWireViewFromGridWire(*gridWire.get());
    }, [this] (const shared_ptr<NodeGridWireView>& gridWire) {
        removeChildComponent(gridWire.get());
    });
    
    resetZOrdering();
    addKeyListener(&nodeGrid.selectionController);
    
    scopedObserve(nodeGrid.draggingWire, [this] (const shared_ptr<NodeGridWire>& draggingWire) {
        if (draggingWire) {
            draggingWireView = makeGridWireViewFromGridWire(*draggingWire.get());
        } else if (draggingWireView) {
            removeChildComponent(draggingWireView.get());
            draggingWireView = nullptr;
        }
    });
}

shared_ptr<NodeGridWireView> NodeGridView::makeGridWireViewFromGridWire(NodeGridWire& nodeGridWire)
{
    NodeGridItemView* emittingGridItem = nullptr;
    NodeGridItemView* receivingGridItem = nullptr;
    SignalView* emittingSignalView = nullptr;
    SignalView* receivingSignalView = nullptr;
    if (nodeGridWire.emittingGridSocket) {
        emittingGridItem = gridItemViewForGridSocket(*nodeGridWire.emittingGridSocket);
        emittingSignalView = emittingGridItem->signalViewFromSignal(*nodeGridWire.emittingGridSocket);
    }
    if (nodeGridWire.receivingGridSocket) {
        receivingGridItem = gridItemViewForGridSocket(*nodeGridWire.receivingGridSocket);
        receivingSignalView = receivingGridItem->signalViewFromSignal(*nodeGridWire.receivingGridSocket);
    }
    auto gridWireView = make_shared<NodeGridWireView>(nodeGridWire, emittingSignalView, emittingGridItem, receivingSignalView, receivingGridItem);
    addAndMakeVisible(gridWireView.get());
    return gridWireView;
}

NodeGridItemView* NodeGridView::gridItemViewForGridSocket(const NodeGridSocket& gridSocket) const
{
    for (const auto& gridItemView : gridItemViews) {
        if (gridItemView->nodeGridItem.containsNodeGridSocket(gridSocket)) {
            return gridItemView.get();
        }
    }
    for (const auto& gridOutputView : gridOutputViews) {
        if (gridOutputView->nodeGridItem.containsNodeGridSocket(gridSocket)) {
            return gridOutputView.get();
        }
    }
    return nullptr;
}

void NodeGridView::resetZOrdering()
{
    for (int i = 0; i < getNumChildComponents(); i++) {
        auto component = dynamic_cast<NodeGridItemView*>(getChildComponent(i));
        if (component) {
            component->toFront(true);
        }
    }
}

#pragma mark - Component

void NodeGridView::paint (Graphics& g)
{
}

void NodeGridView::resized()
{
}

void NodeGridView::parentHierarchyChanged()
{
    if (getParentComponent()) {
        resetZOrdering();
    }
}

void NodeGridView::mouseDown(const MouseEvent& e)
{
    nodeGrid.deselectAll();
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
                nodeGrid.addNode(name, dragSourceDetails.localPosition.x, dragSourceDetails.localPosition.y);
            }
        }
    }
}
