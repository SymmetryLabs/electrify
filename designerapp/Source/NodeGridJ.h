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

//==============================================================================
/*
*/
class NodeGridJ    : public Component
{
public:
    NodeGridJ();
    ~NodeGridJ();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridJ)
};


#endif  // NODEGRIDJ_H_INCLUDED
