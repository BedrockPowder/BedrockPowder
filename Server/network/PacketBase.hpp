//
// Created by pepef on 27.07.2022.
//

#ifndef BEDROCKPOWDER_PACKETBASE_HPP
#define BEDROCKPOWDER_PACKETBASE_HPP

#include "Server/utils/StdEnv.h"
#include "Server/utils/BinaryStream.hpp"

class PacketBase {
public:
    virtual void write(BinaryStream*) = 0;
    virtual void read(BinaryStream*) = 0;
};

#endif //BEDROCKPOWDER_PACKETBASE_HPP
