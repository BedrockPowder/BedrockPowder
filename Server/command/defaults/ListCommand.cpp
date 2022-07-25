//
// Created by pepef on 24.07.2022.
//

#include "Server/command/defaults/ListCommand.h"
#include "Server/BedrockPowder.h"
#include "Server/actor/player/Player.hpp"

ListCommand::ListCommand() : Command("list", "Get list of all players") {}

CommandResult ListCommand::execute(CommandOrigin *ori, std::string alias, std::vector<std::string> args) {
    std::string mMessage = "There are {} of {} players:";
    mMessage = Utils::str_replace(mMessage, "{}", std::to_string(BedrockPowder::getOnlinePlayers()));
    mMessage = Utils::str_replace(mMessage, "{}", BedrockPowder::getServerConfig()->getField("max_players"));
    std::string mMessage_ii;
    if(BedrockPowder::getOnlinePlayers() == 0) {
        mMessage_ii = "No players.";
    } else {
        std::vector<std::string> names{};
        for(auto player : BedrockPowder::getAllPlayers()) {
            names.push_back(player->getName());
        }
        mMessage_ii = Utils::implode(names, ',');
    }
    ori->getActorSender()->sendMessage(mMessage);
    ori->getActorSender()->sendMessage(mMessage_ii);
    return CommandResult::SUCCESS;
}