/*
  ==============================================================================

    NodeListView.cpp
    Created: 3 Aug 2015 5:05:34pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NodeListView.h"

//==============================================================================
NodeListView::NodeListView()
{
    listBox.setModel(this);
    addAndMakeVisible(listBox);
}

#pragma mark - Component

void NodeListView::paintOverChildren(Graphics &g)
{
    g.setColour (Colours::grey);
    g.drawVerticalLine(getRight() - 1, 0, getBottom());
}

void NodeListView::resized()
{
    listBox.setBounds(getLocalBounds());
}

#pragma mark - ListBoxModel

int NodeListView::getNumRows()
{
    return availableNodeNames.size();
}

void NodeListView::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    g.drawText(availableNodeNames[rowNumber], g.getClipBounds(), Justification::centred);
}

var NodeListView::getDragSourceDescription (const SparseSet<int>& rowsToDescribe)
{
    var names;
    int i = 0;
    while (i < rowsToDescribe.size()) {
        int row = rowsToDescribe[i++];
        names.append(var(availableNodeNames[row]));
    }
    return names;
}
