//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_STOPCOMMAND_H
#define BEDROCKPOWDER_STOPCOMMAND_H

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/command/Command.hpp"

class StopCommand : public Command {
public:
    StopCommand();
    CommandResult execute(CommandOrigin* ori, std::string alias, std::vector<std::string> args) override;
};


#endif //BEDROCKPOWDER_STOPCOMMAND_H
