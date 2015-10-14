/*
  ==============================================================================

    Commands.h
    Created: 13 Oct 2015 3:34:43pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "BlueprintUiGlobals.h"

class ProjectDocument;

namespace GeneralCommandIDs
{
    static constexpr int NEW = 0xF001;
    static constexpr int OPEN = 0xF002;
    static constexpr int SAVE = 0xF003;
    static constexpr int SAVE_AS = 0xF004;
}

class Commands : public ApplicationCommandTarget {

public:
    Commands(ProjectDocument& projectDocument, ApplicationCommandManager& commandManager);

    // ApplicationCommandTarget
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(Array<CommandID>& commands) override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform(const InvocationInfo& info) override;

private:
    ProjectDocument& projectDocument;

};

#endif  // COMMANDS_H_INCLUDED
