//
// Created by pepef on 22.07.2022.
//

#include "Server/command/defaults/HelpCommand.h"

HelpCommand::HelpCommand() : Command("help", "Shows list of all available commands.") {}

CommandResult HelpCommand::execute(CommandOrigin *ori, std::string alias, std::vector<std::string> args) {
    std::vector<std::string> message;
    message.push_back("Showing help. (" + std::to_string(BedrockPowder::getCommandManager()->getCommands().size()) + " command(-s) )");
    for(auto command : BedrockPowder::getCommandManager()->getCommands()) {
        message.push_back(command->getName() + ": " + command->getDescription());
    }
    for(const auto& msg_piece : message) {
        ori->getActorSender()->sendMessage(msg_piece);
    }
    return CommandResult::SUCCESS;
}