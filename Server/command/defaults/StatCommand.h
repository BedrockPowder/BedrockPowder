//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_STATCOMMAND_H
#define BEDROCKPOWDER_STATCOMMAND_H

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/command/Command.hpp"
#include "Server/Constants.h"
#include "Server/Network/ProtocolInfo.h"

class StatCommand : public Command {
public:
    StatCommand();
    CommandResult execute(CommandOrigin* ori, std::string alias, std::vector<std::string> args) override;
};

#endif //BEDROCKPOWDER_STATCOMMAND_H