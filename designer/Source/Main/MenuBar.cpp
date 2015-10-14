/*
  ==============================================================================

    MenuBar.cpp
    Created: 13 Oct 2015 1:25:42pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "MenuBar.h"

#include "ProjectDocument.h"
#include "Commands.h"

MenuBar::MenuBar(ApplicationCommandManager& commandManager_)
: commandManager(commandManager_)
{
    setApplicationCommandManagerToWatch(&commandManager);
}

void MenuBar::setupMenu(DocumentWindow& window)
{
    #if JUCE_MAC
        setMacMainMenu(this, nullptr, "Recent");
    #else
        window.setMenuBar(this);
    #endif
}

void MenuBar::takedownMenu(DocumentWindow& window)
{
    #if JUCE_MAC
        setMacMainMenu(nullptr);
    #endif
}

StringArray MenuBar::getMenuBarNames()
{
    const char* const names[] = { "File", nullptr };

    return StringArray (names);
}

PopupMenu MenuBar::getMenuForIndex(int menuIndex, const String& menuName)
{
    PopupMenu menu;

    if (menuIndex == 0) {
        menu.addCommandItem(&commandManager, GeneralCommandIDs::NEW);
        menu.addSeparator();

        menu.addCommandItem(&commandManager, GeneralCommandIDs::OPEN);
        PopupMenu fileMenu;
        menu.addSubMenu("Recent", fileMenu);
        menu.addSeparator();

        menu.addCommandItem(&commandManager, GeneralCommandIDs::SAVE);
        menu.addCommandItem(&commandManager, GeneralCommandIDs::SAVE_AS);
    }

    return menu;
}

void MenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
}
