//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_BEDROCKPOWDER_H
#define BEDROCKPOWDER_BEDROCKPOWDER_H

#include <iostream>

#include "Constants.h"
#include "logger/Logger.hpp"
#include "command/CommandOrigin.hpp"
#include "command/CommandManager.h"
#include "utils/Utils.hpp"

class BedrockPowder {
public:
    static void start();
    static void shutdown();
    static class CommandManager* getCommandManager();
    static class CommandOrigin* getConsoleOrigin();
private:
    int max_players = 20;

};

#endif //BEDROCKPOWDER_BEDROCKPOWDER_H
