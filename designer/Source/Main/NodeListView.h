/*
  ==============================================================================

    NodeListView.h
    Created: 3 Aug 2015 5:05:34pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODELISTJ_H_INCLUDED
#define NODELISTJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <node_registrar.h>

//==============================================================================
/*
*/
class NodeListView : public Component, public ListBoxModel, public DragAndDropContainer {

public:
    NodeListView();

    void paintOverChildren(Graphics &g) override;
    void resized() override;

private:
    NodeRegistrar& nodeRegistrar = NodeRegistrar::getInstance();
    vector<string> availableNodeNames = nodeRegistrar.getAvailableNodeNames();
    
    ListBox listBox;
    
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    var getDragSourceDescription(const SparseSet<int>& rowsToDescribe) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NodeListView)
};


#endif  // NODELISTJ_H_INCLUDED
