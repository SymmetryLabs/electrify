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

//==============================================================================
/*
*/
class NodeListJ    : public Component
{
public:
    NodeListJ();
    ~NodeListJ();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeListJ)
};


#endif  // NODELISTJ_H_INCLUDED
