//
// Created by pepef on 22.07.2022.
//

#include "VersionCommand.h"

VersionCommand::VersionCommand() : Command("version", "Show version of this server", "", {"ver"}) {}

CommandResult VersionCommand::execute(CommandOrigin *ori, string alias, vector<string> args) {
    vector<string> message;
    message.push_back("This server is using " + string(BEDROCKPOWDER_CORE_NAME) + " version " + string(BEDROCKPOWDER_VERSION));
    message.push_back("C++ Version: " + to_string(__cplusplus));
    for(const auto& msg_piece : message) {
        ori->sendMessage(msg_piece);
    }
    return CommandResult::SUCCESS;
}