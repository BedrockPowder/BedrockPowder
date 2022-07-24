//
// Created by pepef on 24.07.2022.
//

#include "Server/command/defaults/ListCommand.h"
#include "Server/BedrockPowder.h"

ListCommand::ListCommand() : Command("list", "Get list of all players") {}

CommandResult ListCommand::execute(CommandOrigin *ori, string alias, vector<string> args) {
    string mMessage = "There are {} of {} players.";
    mMessage = Utils::str_replace(mMessage, "{}", to_string(BedrockPowder::getOnlinePlayers()));
    mMessage = Utils::str_replace(mMessage, "{}", BedrockPowder::getServerConfig()->getField("max_players"));
    ori->getActorSender()->sendMessage(mMessage);
    return CommandResult::SUCCESS;
}