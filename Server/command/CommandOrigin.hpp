//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_COMMANDORIGIN_HPP
#define BEDROCKPOWDER_COMMANDORIGIN_HPP

#include <iostream>

#include "logger/Logger.hpp"

using namespace std;

class CommandOrigin {
public:
    CommandOrigin(const string& name, bool is_player) {
        this->name = name;
        this->is_player = is_player;
    }
    string getName() {
        return this->name;
    }

    void sendMessage(const string& msg) const {
        if(!this->isPlayer()) {
            Logger::log(msg);
            return;
        }
        //...
    }
    [[nodiscard]]
    bool isPlayer() const {
        return is_player;
    };
private:
    string name;
    bool is_player = false;
};

#endif //BEDROCKPOWDER_COMMANDORIGIN_HPP
