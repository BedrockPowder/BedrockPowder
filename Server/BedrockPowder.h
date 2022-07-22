//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_BEDROCKPOWDER_H
#define BEDROCKPOWDER_BEDROCKPOWDER_H

#include "Server/utils/StdEnv.h"

#include <chrono>

#include "Server/command/CommandOrigin.hpp"
#include "Server/command/CommandManager.h"

class BedrockPowder {
public:
    static void start();
    static void shutdown();
    static class CommandManager* getCommandManager();
    static class CommandOrigin* getConsoleOrigin();
    static bool isDevMode();
private:
    int max_players = 20;
};

#endif //BEDROCKPOWDER_BEDROCKPOWDER_H
