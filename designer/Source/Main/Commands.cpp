/*
  ==============================================================================

    Commands.cpp
    Created: 13 Oct 2015 3:34:43pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "Commands.h"

#include "ProjectDocument.h"

Commands::Commands(ProjectDocument& projectDocument_, ApplicationCommandManager& commandManager)
: projectDocument(projectDocument_)
{
    commandManager.registerAllCommandsForTarget(this);
    commandManager.setFirstCommandTarget(this);
}

ApplicationCommandTarget* Commands::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void Commands::getAllCommands(Array<CommandID>& commands)
{
    const CommandID ids[] = {
        GeneralCommandIDs::NEW,
        GeneralCommandIDs::OPEN,
        GeneralCommandIDs::SAVE,
        GeneralCommandIDs::SAVE_AS,
    };

    commands.addArray(ids, numElementsInArray(ids));
}

void Commands::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    const String fileManipulationCategory("File manipulation");

    switch (commandID) {
        case GeneralCommandIDs::NEW:
            result.setInfo("New Project", "Starts a new project", fileManipulationCategory, 0);
            result.addDefaultKeypress('N', ModifierKeys::commandModifier);
            break;
        case GeneralCommandIDs::OPEN:
            result.setInfo("Open...", "Opens a new project", fileManipulationCategory, 0);
            result.addDefaultKeypress('O', ModifierKeys::commandModifier);
            break;
        case GeneralCommandIDs::SAVE:
            result.setInfo("Save", "Saves the current project", fileManipulationCategory, 0);
            result.addDefaultKeypress('S', ModifierKeys::commandModifier);
            break;
        case GeneralCommandIDs::SAVE_AS:
            result.setInfo("Save As...", "Saves the current project as...", fileManipulationCategory, 0);
            result.addDefaultKeypress('S', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
        default:
            break;
    }
}

bool Commands::perform(const InvocationInfo& info)
{
    switch (info.commandID) {
        case GeneralCommandIDs::NEW:
            projectDocument.loadNew();
            break;
        case GeneralCommandIDs::OPEN:
            projectDocument.loadFromUserSpecifiedFile(true);
            break;
        case GeneralCommandIDs::SAVE:
            projectDocument.save(true, true);
            break;
        case GeneralCommandIDs::SAVE_AS:
            projectDocument.saveAsInteractive(true);
            break;
        default:
            return false;
    }
    return true;
}
