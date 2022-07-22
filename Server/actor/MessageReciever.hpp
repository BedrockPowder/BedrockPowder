//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_MESSAGERECIEVER_HPP
#define BEDROCKPOWDER_MESSAGERECIEVER_HPP

#include "Server/utils/StdEnv.h"

#include <utility>

#include "Server/actor/Actor.hpp"

class MessageReciever : public Actor {
public:
    MessageReciever(string name, bool is_player) : Actor(std::move(name), is_player) {}
    virtual void sendMessage(string) = 0;
};

#endif //BEDROCKPOWDER_MESSAGERECIEVER_HPP