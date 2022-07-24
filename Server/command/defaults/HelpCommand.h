//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_HELPCOMMAND_H
#define BEDROCKPOWDER_HELPCOMMAND_H

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/command/Command.hpp"
#include "Server/BedrockPowder.h"

class HelpCommand : public Command {
public:
    HelpCommand();
    CommandResult execute(CommandOrigin* ori, std::string alias, std::vector<std::string> args) override;
};

#endif //BEDROCKPOWDER_HELPCOMMAND_H
