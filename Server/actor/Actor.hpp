//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_ACTOR_HPP
#define BEDROCKPOWDER_ACTOR_HPP

#include "Server/utils/StdEnv.h"

#include <utility>

class Actor {
public:
    Actor(string name, bool is_player) {
        this->name = std::move(name);
        this->is_player = is_player;
    }
    [[nodiscard]]
    bool isPlayer() const {
        return this->is_player;
    }
    string getName() {
        return this->name;
    }
private:
    bool is_player;
    string name;
};

#endif //BEDROCKPOWDER_ACTOR_HPP
