/*
  ==============================================================================

    PropertiesPanel.cpp
    Created: 1 Sep 2015 6:33:01pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PropertiesPanel.h"

//==============================================================================
PropertiesPanel::PropertiesPanel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PropertiesPanel::~PropertiesPanel()
{
}

void PropertiesPanel::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("PropertiesPanel", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PropertiesPanel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
