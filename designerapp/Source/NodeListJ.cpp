/*
  ==============================================================================

    NodeListJ.cpp
    Created: 3 Aug 2015 5:05:34pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NodeListJ.h"

//==============================================================================
NodeListJ::NodeListJ()
{
    listBox.setModel(this);
    addAndMakeVisible(listBox);
}

#pragma mark - Component

void NodeListJ::paint (Graphics& g)
{
}

void NodeListJ::resized()
{
    listBox.setBounds(getLocalBounds());
}

#pragma mark - ListBoxModel

int NodeListJ::getNumRows()
{
    return availableNodeNames.size();
}

void NodeListJ::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    g.drawText(availableNodeNames[rowNumber], g.getClipBounds(), Justification::centred);
}

var NodeListJ::getDragSourceDescription (const SparseSet<int>& rowsToDescribe)
{
    var names;
    int i = 0;
    while (i < rowsToDescribe.size()) {
        int row = rowsToDescribe[i++];
        names.append(var(availableNodeNames[row]));
    }
    return names;
}
