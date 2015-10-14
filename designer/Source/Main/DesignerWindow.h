/*
==============================================================================

    DesignerWindow.h
    Created: 12 Oct 2015 12:39:06pm
    Author:  Kyle Fleming

==============================================================================
*/

#ifndef DESIGNERWINDOW_H_INCLUDED
#define DESIGNERWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <engine.h>
#include <session.h>

#include "ProjectDocument.h"
#include "DesignerWindowComponent.h"
#include "MenuBar.h"

//==============================================================================
/*
 This class implements the desktop window that contains an instance of
 our MainContentNode class.
 */
class DesignerWindow    : public DocumentWindow {
public:
    DesignerWindow(String name,
                   unique_ptr<ProjectDocument>&& projectDocument_,
                   UiSession& session,
                   ApplicationCommandManager& applicationCommandManager,
                   MenuBar& menuBar_)
    : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
    , projectDocument(move(projectDocument_))
    , menuBar(menuBar_)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new DesignerWindowComponent(session), true);
        setResizable(true, true);
        
        centreWithSize(getWidth(), getHeight());
        setBounds(getBounds().withY(0));
        setVisible(true);

        addKeyListener(applicationCommandManager.getKeyMappings());

        menuBar.setupMenu(*this);
    }

    ~DesignerWindow()
    {
        menuBar.takedownMenu(*this);
    }
    
    void closeButtonPressed() override
    {
        // This is called when the user tries to close this window. Here, we'll just
        // ask the app to quit when this happens, but you can change this to do
        // whatever you need.
        JUCEApplication::getInstance()->systemRequestedQuit();
    }
    
    /* Note: Be careful if you override any DocumentWindow methods - the base
     class uses a lot of them, so by overriding you might break its functionality.
     It's best to do all your work in your content node instead, but if
     you really have to override any DocumentWindow methods, make sure your
     subclass also calls the superclass's method.
     */
    
private:
    unique_ptr<ProjectDocument> projectDocument;
    MenuBar& menuBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DesignerWindow)
};


#endif  // DESIGNERWINDOW_H_INCLUDED
