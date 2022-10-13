//
// Created by pepef on 22.07.2022.
//

#include "Server/command/CommandManager.h"

#include "Server/utils/Utils.hpp"
#include "Server/logger/Logger.hpp"

#include "Server/command/defaults/StopCommand.h"
#include "Server/command/defaults/HelpCommand.h"
#include "Server/command/defaults/ListCommand.h"
#include "Server/command/defaults/VersionCommand.h"
#include "Server/command/defaults/SayCommand.h"
#include "Server/command/defaults/StatCommand.h"

void CommandManager::init() {
    this->registerCommand(new HelpCommand());
    this->registerCommand(new StopCommand());
    this->registerCommand(new ListCommand());
    this->registerCommand(new VersionCommand());
    this->registerCommand(new SayCommand());
    this->registerCommand(new StatCommand());
}

void CommandManager::registerCommand(class Command* cmd) {
    Logger::log("Registered command: " + cmd->getName(), LogLevel::DEBUG);
    this->command_map.push_back(cmd);
}

void CommandManager::handleCommandRequest(CommandOrigin* origin, const std::string& cmd, const std::vector<std::string>& args) {
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
    std::string message_unk = BedrockPowder::getLangConfig()->getTranslatedString("unk_command_message");
    message_unk = Utils::str_replace(message_unk, "{}", cmd);
    if(found == nullptr) {
        origin->getActorSender()->sendMessage(message_unk);
        return;
    }
    if(found->execute(origin, cmd, args) == CommandResult::FAILED) {
        origin->getActorSender()->sendMessage(message_unk);
    }
}