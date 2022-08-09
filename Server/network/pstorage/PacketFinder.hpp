//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_PACKETFINDER_HPP
#define BEDROCKPOWDER_PACKETFINDER_HPP

#include "Server/BedrockPowder.h"
#include "Server/network/pstorage/PacketStorage.hpp"

template<typename PTy>
class PacketFinder {
public:
    explicit PacketFinder(int pid) {
        this->pid = pid;
    }

    PTy* return_() {
        return (PTy*) BedrockPowder::getPacketStorage()->getPacket(this->pid);
    }
private:
    int pid{};
};

#endif //BEDROCKPOWDER_PACKETFINDER_HPP
