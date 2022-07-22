//
// Created by pepef on 22.07.2022.
//

#include "CommandManager.h"

void CommandManager::addCommand(class Command* cmd) {
    this->command_map.push_back(cmd);
}

void CommandManager::tryExecute(CommandOrigin* origin, const string& cmd, const vector<string>& args) {
    Command* found = nullptr;
    for(auto cmd_f_m : this->command_map) {
        bool is_break001 = false;
        for(const auto& alias : cmd_f_m->getAliases()) {
            if(alias == cmd) {
                is_break001 = true;
                found = cmd_f_m;
                break;
            }
        }
        if(is_break001) {
            break;
        }
        if(cmd_f_m->getName() == cmd) {
            found = cmd_f_m;
            break;
        }
    }
    if(found == nullptr) {
        origin->sendMessage("Unknown command: " + cmd + ". Use command /help to get all available commands.");
        return;
    }
    found->execute(origin, cmd, args);
}