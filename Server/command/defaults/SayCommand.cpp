//
// Created by pepef on 09.08.2022.
//

#include "Server/command/defaults/SayCommand.h"

SayCommand::SayCommand() : Command("say", "Broadcasts the message to all", "/say <message...>") {}

CommandResult SayCommand::execute(CommandOrigin *ori, std::string alias, std::vector<std::string> args) {
    if(args.size() == 0) {
        ori->getActorSender()->sendMessage(this->getUsage());
        return CommandResult::SUCCESS;
    }
    std::string message = "[" + ori->getActorSender()->getName() + "] " + Utils::implode(args, ' ');
    BedrockPowder::getConsoleOrigin()->getActorSender()->sendMessage(message);
    return CommandResult::SUCCESS;
}