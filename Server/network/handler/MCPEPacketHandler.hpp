//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_MCPEPACKETHANDLER_HPP
#define BEDROCKPOWDER_MCPEPACKETHANDLER_HPP

#include "Server/network/packets/LoginPacket.hpp"

class MCPEPacketHandler {
public:
    MCPEPacketHandler() = default;

    void handleLoginPacket(LoginPacket* packet) {}
    void handlePlayStatus()
};

#endif //BEDROCKPOWDER_MCPEPACKETHANDLER_HPP
