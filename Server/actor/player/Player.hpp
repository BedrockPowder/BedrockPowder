//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_PLAYER_HPP
#define BEDROCKPOWDER_PLAYER_HPP

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"
#include "Server/actor/Actor.hpp"
#include "Server/actor/Mob.hpp"

class Player : public MessageReciever {
public:
    Player(std::string name1, bool isPlayer, std::string name) : MessageReciever(name1, isPlayer) /*Mob(std::move(name), true)*/ {
        //this->name = name;
    }
};

#endif //BEDROCKPOWDER_PLAYER_HPP