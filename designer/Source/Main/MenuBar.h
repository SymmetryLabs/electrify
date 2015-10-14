/*
  ==============================================================================

    MenuBar.h
    Created: 13 Oct 2015 1:25:42pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef MENUBAR_H_INCLUDED
#define MENUBAR_H_INCLUDED

#include "BlueprintUiGlobals.h"

class ProjectDocument;

class MenuBar : public MenuBarModel {

public:
    explicit MenuBar(ApplicationCommandManager& commandManager);

    void setupMenu(DocumentWindow& window);
    void takedownMenu(DocumentWindow& window);

    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int menuIndex, const String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:
    ApplicationCommandManager& commandManager;

};

#endif  // MENUBAR_H_INCLUDED
