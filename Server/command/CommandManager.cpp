//
// Created by pepef on 22.07.2022.
//

#include "Server/command/CommandManager.h"

#include "Server/utils/Utils.hpp"
#include "Server/logger/Logger.hpp"

void CommandManager::addCommand(class Command* cmd) {
    Logger::log("Added command: " + cmd->getName(), LogLevel::DEBUG);
    this->command_map.push_back(cmd);
}

void CommandManager::tryExecute(CommandOrigin* origin, const string& cmd, const vector<string>& args) {
    Command* found = nullptr;
    for(auto cmd_f_m : this->command_map) {
        bool should_break = false;
        for(const auto& alias : cmd_f_m->getAliases()) {
            if(alias == cmd) {
                should_break = true;
                found = cmd_f_m;
                break;
            }
        }
        if(should_break) {
            break;
        }
        if(cmd_f_m->getName() == cmd) {
            found = cmd_f_m;
            break;
        }
    }
    string message_unk = BedrockPowder::getLangConfig()->getTranslatedString("unk_command_message");
    if(found == nullptr) {
        origin->getActorSender()->sendMessage(message_unk);
        return;
    }
    if(found->execute(origin, cmd, args) == CommandResult::FAILED) {
        origin->getActorSender()->sendMessage(message_unk);
    }
}