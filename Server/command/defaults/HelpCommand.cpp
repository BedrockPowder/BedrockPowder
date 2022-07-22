//
// Created by pepef on 22.07.2022.
//

#include "HelpCommand.h"

HelpCommand::HelpCommand() : Command("help", "Shows list of all available commands.") {}

CommandResult HelpCommand::execute(CommandOrigin *ori, string alias, vector<string> args) {
    vector<string> message;
    message.push_back("Showing help. (" + to_string(BedrockPowder::getCommandManager()->getCommands().size()) + " command(-s) )");
    for(auto command : BedrockPowder::getCommandManager()->getCommands()) {
        message.push_back(command->getName() + ": " + command->getDescription());
    }
    for(const auto& msg_piece : message) {
        ori->sendMessage(msg_piece);
    }
    return CommandResult::SUCCESS;
}