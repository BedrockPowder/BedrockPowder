//
// Created by pepef on 22.07.2022.
//

#include "Server/command/defaults/StopCommand.h"
#include "Server/BedrockPowder.h"

StopCommand::StopCommand() : Command("stop", "Stops the server") {}

CommandResult StopCommand::execute(CommandOrigin *ori, std::string alias, std::vector<std::string> args) {
    BedrockPowder::shutdown();
    return CommandResult::SUCCESS;
}