/*
  ==============================================================================

    NodeGridView.h
    Created: 3 Aug 2015 5:05:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDJ_H_INCLUDED
#define NODEGRIDJ_H_INCLUDED

#include "BlueprintUiGlobals.h"

#include "NodeGrid.h"
#include "NodeGridItemView.h"
#include "NodeGridWireView.h"

//==============================================================================
/*
*/
class NodeGridView : public Component, public DragAndDropTarget, public Observes {
    
public:
    explicit NodeGridView(NodeGrid& nodeGrid);

private:
    
    NodeGrid& nodeGrid;
    
    ObservableVector<shared_ptr<NodeGridItemView>> gridItemViews;
    ObservableVector<shared_ptr<NodeGridWireView>> gridWireViews;
    ObservableVector<shared_ptr<NodeGridItemView>> gridOutputViews;
    
    shared_ptr<NodeGridWireView> draggingWireView;
    
    shared_ptr<NodeGridWireView> makeGridWireViewFromGridWire(NodeGridWire& nodeGridWire);
    NodeGridItemView* gridItemViewForGridSocket(const NodeGridSocket& gridSocket) const;
    
    void resetZOrdering();
    
    void paint (Graphics&) override;
    void resized() override;
    void parentHierarchyChanged() override;
    void mouseDown(const MouseEvent& e) override;
    
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    void itemDropped (const SourceDetails& dragSourceDetails) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridView)
};


#endif  // NODEGRIDJ_H_INCLUDED
