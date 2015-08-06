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
        if (nodeGrid != nullptr) {
            for (const shared_ptr<NodeGridItem>& gridItem : nodeGrid->gridItems) {
                addWithGridItem(gridItem.get());
            }
        }
    });
    
    this->nodeGrid <<= nodeGrid_;
    
    observeWithCapture(nodeGrid.Value()->gridItems.valueAdded, [this] (const pair<size_t, reference_wrapper<shared_ptr<NodeGridItem>>>& p) {
        addWithGridItem(p.second.get().get());
    });
    
    observeWithCapture(nodeGrid.Value()->gridItems.valueRemoved, [this] (const pair<size_t, shared_ptr<NodeGridItem>>& p) {
        removeWithGridItem(p.second.get());
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
