//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_LISTCOMMAND_H
#define BEDROCKPOWDER_LISTCOMMAND_H

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/command/Command.hpp"

class ListCommand : public Command {
public:
    ListCommand();
    CommandResult execute(CommandOrigin* ori, std::string alias, std::vector<std::string> args) override;
};


#endif //BEDROCKPOWDER_LISTCOMMAND_H
