//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_STOPCOMMAND_H
#define BEDROCKPOWDER_STOPCOMMAND_H

#include <iostream>

#include "../Command.hpp"
#include "../../BedrockPowder.h"

using namespace std;

class StopCommand : public Command {
public:
    StopCommand();
    CommandResult execute(CommandOrigin* ori, string alias, vector<string> args) override;
};


#endif //BEDROCKPOWDER_STOPCOMMAND_H
