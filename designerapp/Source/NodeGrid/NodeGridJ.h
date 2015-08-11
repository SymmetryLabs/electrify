/*
  ==============================================================================

    NodeGridJ.h
    Created: 3 Aug 2015 5:05:45pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDJ_H_INCLUDED
#define NODEGRIDJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "node_grid.h"
#include "NodeGridItemJ.h"
#include "NodeGridWireView.h"

//==============================================================================
/*
*/
class NodeGridJ    : public Component, public DragAndDropTarget, public Observes<EngineUiDomain>
{
    USING_REACTIVE_DOMAIN(EngineUiDomain)
    
public:
    NodeGridJ(NodeGrid* nodeGrid);

private:
    
    VarSignalT<NodeGrid*> nodeGrid = MakeVar<EngineUiDomain, NodeGrid*>(nullptr);
    
    vector<unique_ptr<NodeGridItemJ>> gridItems;
    vector<unique_ptr<NodeGridWireView>> gridWireViews;
    
    void addWithGridItem(NodeGridItem* gridItem);
    void removeWithGridItem(NodeGridItem* gridItem);
    void removeAllGridItems();
    
    NodeGridItemJ* gridItemViewWithGridItem(NodeGridItem& gridItem);
    
    void addViewWithGridWire(NodeGridWire* gridWire);
    void removeViewWithGridWire(NodeGridWire* gridWire);
    void removeAllGridWireViews();
    
    void paint (Graphics&) override;
    void resized() override;
    void mouseDrag (const MouseEvent& event) override;
    
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    void itemDropped (const SourceDetails& dragSourceDetails) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridJ)
};


#endif  // NODEGRIDJ_H_INCLUDED
