//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_SAYCOMMAND_H
#define BEDROCKPOWDER_SAYCOMMAND_H


#include "Server/actor/MessageReciever.hpp"
#include "Server/command/Command.hpp"
#include "Server/BedrockPowder.h"

class SayCommand : public Command {
public:
    SayCommand();
    CommandResult execute(CommandOrigin* ori, std::string alias, std::vector<std::string> args) override;
};


#endif //BEDROCKPOWDER_SAYCOMMAND_H
