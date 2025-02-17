/*
  ==============================================================================

    NodeGridItemView.h
    Created: 3 Aug 2015 5:05:56pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDITEMJ_H_INCLUDED
#define NODEGRIDITEMJ_H_INCLUDED

#include "BlueprintUiGlobals.h"

#include <observes.h>
#include <node_socket.h>

#include "NodeGridItem.h"
#include "SignalView.h"
#include "NodeGrid.h"

//==============================================================================
/*
*/
class NodeGridItemView : public Component, public Observes
{
public:
    NodeGridItemView(NodeGridItem& nodeGridItem, NodeGrid& nodeGrid);
    
    void setPos(Point<int> pos);
    
    NodeGridItem& nodeGridItem;
    NodeGrid& nodeGrid;
    
    SignalView* signalViewFromSignal(const NodeGridSocket& gridSocket) const;
    
    void paint(Graphics&) override;
    void resized() override;
    
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;

private:
    
    vector<unique_ptr<SignalView>> signalViews;
    
    ComponentDragger dragger;
    bool dragStarted = false;
    
    bool focused = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridItemView)
};


#endif  // NODEGRIDITEMJ_H_INCLUDED
