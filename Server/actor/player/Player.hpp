//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_PLAYER_HPP
#define BEDROCKPOWDER_PLAYER_HPP

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/actor/Actor.hpp"
#include "Server/actor/Mob.hpp"

class Player : MessageReciever, Mob {
public:
    Player(std::string name) : MessageReciever(std::move(name), true), Mob(std::move(name), true) {}
};

#endif //BEDROCKPOWDER_PLAYER_HPP
