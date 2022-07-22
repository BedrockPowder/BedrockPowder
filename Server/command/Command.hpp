//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_COMMAND_HPP
#define BEDROCKPOWDER_COMMAND_HPP

#include <iostream>
#include <vector>

#include "CommandOrigin.hpp"

using namespace std;

enum CommandResult {
    FAILED,
    SUCCESS
};

class Command {
public:
    explicit Command(const string& cmd_name, const string& description = "", const string& usage_message = "", const vector<string>& aliases = {}) {
        this->name = cmd_name;
        this->desc = description;
        this->usage = usage_message;
        this->aliases_list = aliases;
    }
    // CommandResult execute (sender, command, args)
    virtual CommandResult execute(CommandOrigin*, string, vector<string>) = 0;
    string getName() {
        return this->name;
    }
    string getDescription() {
        return this->desc;
    }
    string getUsage() {
        return this->usage;
    }
    vector<string> getAliases() {
        return this->aliases_list;
    }
private:
    string name;
    string desc;
    string usage;
    vector<string> aliases_list;
};

#endif //BEDROCKPOWDER_COMMAND_HPP
