//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_COMMAND_HPP
#define BEDROCKPOWDER_COMMAND_HPP

#include "Server/utils/StdEnv.h"

#include <vector>

#include "Server/command/CommandOrigin.hpp"

enum CommandResult {
    FAILED,
    SUCCESS
};

class Command {
public:
    explicit Command(const std::string& cmd_name, const std::string& description = "", const std::string& usage_message = "", const std::vector<std::string>& aliases = {}) {
        this->name = cmd_name;
        this->desc = description;
        this->usage = usage_message;
        this->aliases_list = aliases;
    }
    // CommandResult execute (sender, command, args)
    virtual CommandResult execute(CommandOrigin*, std::string, std::vector<std::string>) = 0;
    std::string getName() {
        return this->name;
    }
    std::string getDescription() {
        return this->desc;
    }
    std::string getUsage() {
        return this->usage;
    }
    std::vector<std::string> getAliases() {
        return this->aliases_list;
    }
private:
    std::string name;
    std::string desc;
    std::string usage;
    std::vector<std::string> aliases_list;
};

#endif //BEDROCKPOWDER_COMMAND_HPP
