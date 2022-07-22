//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_HELPCOMMAND_H
#define BEDROCKPOWDER_HELPCOMMAND_H

#include <iostream>

#include "../Command.hpp"
#include "../../BedrockPowder.h"

using namespace std;

class HelpCommand : public Command {
public:
    HelpCommand();
    CommandResult execute(CommandOrigin* ori, string alias, vector<string> args) override;
};

#endif //BEDROCKPOWDER_HELPCOMMAND_H
