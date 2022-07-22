//
// Created by pepef on 22.07.2022.
//

#include "StopCommand.h"

StopCommand::StopCommand() : Command("stop", "Stops the server") {}

CommandResult StopCommand::execute(CommandOrigin *ori, string alias, vector<string> args) {
    BedrockPowder::shutdown();
    return CommandResult::SUCCESS;
}