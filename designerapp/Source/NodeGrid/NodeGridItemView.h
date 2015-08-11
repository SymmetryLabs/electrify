/*
  ==============================================================================

    NodeGridItemView.h
    Created: 3 Aug 2015 5:05:56pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDITEMJ_H_INCLUDED
#define NODEGRIDITEMJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <observes.h>

#include "NodeGridItem.h"
#include "SignalView.h"

//==============================================================================
/*
*/
class NodeGridItemView    : public Component, public Observes<EngineUiDomain>
{
public:
    NodeGridItemView(NodeGridItem& nodeGridItem);
    
    void setPos(Point<int> pos);
    
    NodeGridItem& nodeGridItem;
    
    SignalView* signalViewFromSignal(string& signalName);

private:
    
    vector<unique_ptr<SignalView>> signalViews;
    
    ComponentDragger dragger;
    bool dragStarted;
    
    bool focused;
    
    void paint(Graphics&) override;
    void resized() override;
    
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent&) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridItemView)
};


#endif  // NODEGRIDITEMJ_H_INCLUDED
