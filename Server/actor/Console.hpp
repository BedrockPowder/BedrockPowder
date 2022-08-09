//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_CONSOLE_HPP
#define BEDROCKPOWDER_CONSOLE_HPP

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/logger/Logger.hpp"

class Console : public MessageReciever {
public:
    Console(std::string name, bool isPlayer) : MessageReciever(name, isPlayer) {}
    void sendMessage(std::string message) override {
        Logger::log(message);
    }
};

#endif //BEDROCKPOWDER_CONSOLE_HPP
