//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_COMMANDORIGIN_HPP
#define BEDROCKPOWDER_COMMANDORIGIN_HPP

#include "Server/utils/StdEnv.h"

#include "Server/actor/MessageReciever.hpp"

class CommandOrigin {
public:
    explicit CommandOrigin(MessageReciever* actor_origin) {
        this->actor_ori = actor_origin;
    }
    class MessageReciever* getActorSender() {
        return this->actor_ori;
    }
private:
    class MessageReciever* actor_ori;
};

#endif //BEDROCKPOWDER_COMMANDORIGIN_HPP
