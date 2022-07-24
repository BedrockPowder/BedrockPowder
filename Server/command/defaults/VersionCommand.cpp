//
// Created by pepef on 22.07.2022.
//

#include "Server/command/defaults/VersionCommand.h"

VersionCommand::VersionCommand() : Command("version", "Show version of this server", "", {"ver"}) {}

CommandResult VersionCommand::execute(CommandOrigin *ori, std::string alias, std::vector<std::string> args) {
    std::vector<std::string> message;
    message.push_back("This server is using " + std::string(BEDROCKPOWDER_CORE_NAME) + " version " + std::string(BEDROCKPOWDER_VERSION));
    message.push_back("C++ Version: " + std::to_string(__cplusplus));
    for(const auto& msg_piece : message) {
        ori->getActorSender()->sendMessage(msg_piece);
    }
    return CommandResult::SUCCESS;
}