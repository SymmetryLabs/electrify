/*
  ==============================================================================

    PropertiesPanel.h
    Created: 1 Sep 2015 6:33:01pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef PROPERTIESPANEL_H_INCLUDED
#define PROPERTIESPANEL_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PropertiesPanel    : public Component
{
public:
    PropertiesPanel();
    ~PropertiesPanel();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertiesPanel)
};


#endif  // PROPERTIESPANEL_H_INCLUDED
