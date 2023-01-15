//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_MCPEPACKET_HPP
#define BEDROCKPOWDER_MCPEPACKET_HPP

#include "Server/utils/StdEnv.h"
#include "Server/network/PacketBase.hpp"
#include "Server/utils/BinaryStream.hpp"

template<typename PTy>
class MCPEPacket : public PTy, public PacketBase {
public:
    explicit MCPEPacket(int packet_id) {
        this->packet_id = packet_id;
    }

    void readHeader(BinaryStream* stream) {
        this->packet_id = stream->get_var_int();
        if (this->packet_id == -1) {
            Logger::log("ERROR: the packet should be positive");
            return;
        }
        this->read(stream);
    }

    void writeHeader(BinaryStream* stream) {
        stream->put_var_int(this->packet_id);
        this->write(stream);
    }

    int PID() {
        return this->packet_id;
    }
protected:
    int packet_id{};
};

#endif //BEDROCKPOWDER_MCPEPACKET_HPP
