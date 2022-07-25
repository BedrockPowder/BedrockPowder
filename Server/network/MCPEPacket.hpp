//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_MCPEPACKET_HPP
#define BEDROCKPOWDER_MCPEPACKET_HPP

#include "Server/utils/StdEnv.h"
#include "Server/utils/BinaryStream.hpp"

template<typename PTy>
class MCPEPacket : PTy {
public:
    explicit MCPEPacket(int packet_id) {
        this->packet_id = packet_id;
    }
    virtual void write(BinaryStream*) = 0;
    virtual void read(BinaryStream*) = 0;
private:
    int packet_id{};
};

#endif //BEDROCKPOWDER_MCPEPACKET_HPP
