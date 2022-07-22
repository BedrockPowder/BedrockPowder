//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_VERSIONCOMMAND_H
#define BEDROCKPOWDER_VERSIONCOMMAND_H

#include <iostream>

#include "../Command.hpp"
#include "../../BedrockPowder.h"

using namespace std;

class VersionCommand : public Command {
public:
    VersionCommand();
    CommandResult execute(CommandOrigin* ori, string alias, vector<string> args) override;
};

#endif //BEDROCKPOWDER_VERSIONCOMMAND_H
