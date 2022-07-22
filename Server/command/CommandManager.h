//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_COMMANDMANAGER_H
#define BEDROCKPOWDER_COMMANDMANAGER_H

#include "Server/utils/StdEnv.h"

#include <map>
#include <vector>

#include "Server/actor/MessageReciever.hpp"
#include "Server/command/CommandOrigin.hpp"
#include "Server/command/Command.hpp"

class CommandManager {
public:
    CommandManager() = default;
    void addCommand(class Command*);
    vector<class Command*> getCommands() {
        return this->command_map;
    }
    void tryExecute(CommandOrigin*, const string&, const vector<string>&);
private:
    vector<class Command*> command_map;
};


#endif //BEDROCKPOWDER_COMMANDMANAGER_H
