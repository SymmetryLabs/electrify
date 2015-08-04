/*
  ==============================================================================

    NodeListJ.h
    Created: 3 Aug 2015 5:05:34pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODELISTJ_H_INCLUDED
#define NODELISTJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "blueprint_ui_globals.h"
#include "node_registrar.h"

//==============================================================================
/*
*/
class NodeListJ    : public Component, public ListBoxModel, public DragAndDropContainer
{
public:
    NodeListJ();

    void paint (Graphics&);
    void resized();

private:
    
    NodeRegistrar nodeRegistrar;
    vector<string> availableNodeNames = nodeRegistrar.getAvailableNodeNames();
    
    ListBox listBox;
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    var getDragSourceDescription (const SparseSet<int>& rowsToDescribe) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeListJ)
};


#endif  // NODELISTJ_H_INCLUDED
