/*
  ==============================================================================

    NodeGridItemJ.h
    Created: 3 Aug 2015 5:05:56pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef NODEGRIDITEMJ_H_INCLUDED
#define NODEGRIDITEMJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class NodeGridItemJ    : public Component
{
public:
    NodeGridItemJ();
    ~NodeGridItemJ();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NodeGridItemJ)
};


#endif  // NODEGRIDITEMJ_H_INCLUDED
