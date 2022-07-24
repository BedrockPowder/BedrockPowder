//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_BEDROCKPOWDER_H
#define BEDROCKPOWDER_BEDROCKPOWDER_H

#include "Server/command/CommandOrigin.hpp"
#include "Server/command/CommandManager.h"
#include "Server/config/LangConfiguration.hpp"
#include "Server/config/ServerConfiguration.hpp"

class BedrockPowder {
public:
    static void start();
    static void shutdown();
    static int getOnlinePlayers();
    static class CommandManager* getCommandManager();
    static class ServerConfiguration* getServerConfig();
    static class CommandOrigin* getConsoleOrigin();
    static bool isDebugMessagesEnabled();
    static class LangConfiguration* getLangConfig();
};

#endif //BEDROCKPOWDER_BEDROCKPOWDER_H
