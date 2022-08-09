//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_PACKETSTORAGE_HPP
#define BEDROCKPOWDER_PACKETSTORAGE_HPP

#include "Server/utils/StdEnv.h"
#include "Server/network/MCPEPacket.hpp"
#include "Server/network/PacketType.hpp"
#include <vector>

class PacketStorage {
public:
    PacketStorage() = default;

    void registerPacket(MCPEPacket<ServerSide>* packet) {
        this->server_side_packets.push_back(packet);
    }

    void registerPacket(MCPEPacket<ClientSide>* packet) {
        this->client_side_packets.push_back(packet);
    }

    void registerPacket(MCPEPacket<AllSide>* packet) {
        this->all_side_packets.push_back(packet);
    }

    void* getPacket(int pid) {
        for(auto packet : this->server_side_packets) {
            if(packet->PID() == pid) {
                return packet;
            }
        }
        for(auto packet : this->client_side_packets) {
            if(packet->PID() == pid) {
                return packet;
            }
        }
        for(auto packet : this->all_side_packets) {
            if(packet->PID() == pid) {
                return packet;
            }
        }
        return nullptr;
    }
private:
    std::vector<MCPEPacket<ServerSide>*> server_side_packets{};
    std::vector<MCPEPacket<ClientSide>*> client_side_packets{};
    std::vector<MCPEPacket<AllSide>*> all_side_packets{};
};

#endif //BEDROCKPOWDER_PACKETSTORAGE_HPP
