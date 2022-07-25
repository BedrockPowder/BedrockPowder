//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_MOB_HPP
#define BEDROCKPOWDER_MOB_HPP

#include "Server/utils/StdEnv.h"

#include "Server/actor/Actor.hpp"

class Mob : public Actor {
public:
    Mob(std::string name, bool is_player) : Actor(std::move(name), is_player) {}
};

#endif //BEDROCKPOWDER_MOB_HPP
